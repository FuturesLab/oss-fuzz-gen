#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzz data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string to create a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // If json_obj is not NULL, call the function-under-test
    if (json_obj != nullptr) {
        int32_t result = json_object_get_int(json_obj);
        // Use the result to prevent compiler optimizations
        (void)result;

        // Free the json_object
        json_object_put(json_obj);
    }

    return 0;
}