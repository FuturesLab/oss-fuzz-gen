#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the string into a JSON object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());

    // Check if the JSON object was created successfully
    if (jobj != nullptr) {
        // Call the function under test
        int string_len = json_object_get_string_len(jobj);

        // Decrement the reference count on the JSON object
        json_object_put(jobj);
    }

    return 0;
}