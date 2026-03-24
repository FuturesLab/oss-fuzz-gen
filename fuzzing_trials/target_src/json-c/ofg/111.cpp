#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a JSON object to act as the array
    struct json_object *array_obj = json_object_new_array();

    // Create a JSON object to insert into the array
    struct json_object *element_obj = json_object_new_object();

    // Ensure there is at least one byte to consume for the index
    if (fuzzed_data.remaining_bytes() < sizeof(size_t)) {
        json_object_put(array_obj);
        json_object_put(element_obj);
        return 0;
    }

    // Consume a size_t value for the index
    size_t index = fuzzed_data.ConsumeIntegral<size_t>();

    // Call the function-under-test
    json_object_array_put_idx(array_obj, index, element_obj);

    // Clean up
    json_object_put(array_obj);
    json_object_put(element_obj);

    return 0;
}