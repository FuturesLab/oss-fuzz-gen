#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the input data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Create a json_object from the string
    struct json_object *jobj = json_tokener_parse(json_string.c_str());

    // If parsing was successful, call the function under test
    if (jobj != nullptr) {
        const char *result = json_object_get_string(jobj);
        // Use the result in some way to avoid compiler optimizations
        if (result) {
            volatile size_t result_length = strlen(result);
            (void)result_length;
        }
        // Free the json_object after use
        json_object_put(jobj);
    }

    return 0;
}