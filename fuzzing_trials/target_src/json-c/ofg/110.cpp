#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a portion of the data to create a json_object for the array
    std::string array_data = fuzzed_data.ConsumeRandomLengthString();
    struct json_object *json_array = json_tokener_parse(array_data.c_str());
    if (!json_array) {
        return 0; // Exit if json_array creation failed
    }

    // Consume a size_t index
    size_t index = fuzzed_data.ConsumeIntegral<size_t>();

    // Consume remaining data to create another json_object
    std::string obj_data = fuzzed_data.ConsumeRemainingBytesAsString();
    struct json_object *json_obj = json_tokener_parse(obj_data.c_str());
    if (!json_obj) {
        json_object_put(json_array); // Clean up before exiting
        return 0; // Exit if json_obj creation failed
    }

    // Call the function-under-test
    json_object_array_put_idx(json_array, index, json_obj);

    // Clean up
    json_object_put(json_array);
    json_object_put(json_obj);

    return 0;
}