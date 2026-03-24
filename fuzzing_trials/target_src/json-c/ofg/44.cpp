#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h" // Correct path for json_object functions
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the provided data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a JSON object
    json_object *json_obj = json_object_new_array();

    // Determine the number of elements to add to the JSON array
    size_t num_elements = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 10);

    // Add elements to the JSON array
    for (size_t i = 0; i < num_elements && fuzzed_data.remaining_bytes() > 0; ++i) {
        int element = fuzzed_data.ConsumeIntegral<int>();
        json_object_array_add(json_obj, json_object_new_int(element));
    }

    // Determine the new size to shrink the array to
    int new_size = fuzzed_data.ConsumeIntegralInRange<int>(0, num_elements);

    // Call the function-under-test
    json_object_array_shrink(json_obj, new_size);

    // Clean up the JSON object
    json_object_put(json_obj);

    return 0;
}