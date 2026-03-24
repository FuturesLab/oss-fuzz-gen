#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRandomLengthString(1024);

    // Parse the JSON string to a JSON object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Ensure the JSON object is an array
    if (!json_obj || !json_object_is_type(json_obj, json_type_array)) {
        if (json_obj) {
            json_object_put(json_obj); // Free the JSON object if not NULL
        }
        return 0;
    }

    // Get the length of the JSON array
    size_t array_length = json_object_array_length(json_obj);

    // Consume an index within the range of the array length
    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, array_length > 0 ? array_length - 1 : 0);

    // Call the function-under-test
    struct json_object *result = json_object_array_get_idx(json_obj, index);

    // Clean up
    json_object_put(json_obj);

    return 0;
}