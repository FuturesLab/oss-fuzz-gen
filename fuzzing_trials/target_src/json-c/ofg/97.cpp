#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Create a FuzzedDataProvider to handle the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a portion of the input data as a random length string to create a JSON object
    std::string json_str = fuzzed_data.ConsumeRandomLengthString(fuzzed_data.remaining_bytes());

    // Check if the string is non-empty
    if (!json_str.empty()) {
        // Parse the JSON string to create a json_object
        struct json_object *jobj = json_tokener_parse(json_str.c_str());

        // Ensure the json_object is not NULL
        if (jobj != nullptr) {
            // Call the function-under-test
            uint64_t result = json_object_get_uint64(jobj);

            // Clean up the JSON object
            json_object_put(jobj);
        }
    }

    return 0;
}