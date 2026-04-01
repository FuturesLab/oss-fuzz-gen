#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string for the JSON key
    std::string key = fuzzed_data.ConsumeRandomLengthString();

    // Consume the remaining bytes to create a JSON object string
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string into a json_object
    json_object *json_obj = json_tokener_parse(json_str.c_str());

    // Ensure the json_obj is not NULL
    if (json_obj != NULL) {
        // Call the function-under-test
        json_object *result = json_object_object_get(json_obj, key.c_str());

        // Decrement the reference count of the JSON object
        json_object_put(json_obj);
    }

    return 0;
}