#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string to create a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Ensure the json_object is not NULL before calling the function
    if (json_obj != nullptr) {
        // Call the function-under-test
        struct json_object *result = json_object_get(json_obj);

        // Decrement the reference count for the json_object
        json_object_put(json_obj);

        // If result is not NULL, decrement its reference count as well
        if (result != nullptr) {
            json_object_put(result);
        }
    }

    return 0;
}