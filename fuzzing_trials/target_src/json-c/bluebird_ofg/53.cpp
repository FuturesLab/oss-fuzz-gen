#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new JSON object array
    json_object *json_array = json_object_new_array();
    if (!json_array) {
        return 0;
    }

    // Populate the JSON array with some elements
    size_t num_elements = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 10);
    for (size_t i = 0; i < num_elements; ++i) {
        json_object *jint = json_object_new_int(fuzzed_data.ConsumeIntegral<int>());

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function json_object_array_add with json_object_equal
        json_object_equal(json_array, jint);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Get index and count for deletion
    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, num_elements - 1);
    size_t count = fuzzed_data.ConsumeIntegralInRange<size_t>(0, num_elements - index);

    // Call the function under test
    json_object_array_del_idx(json_array, index, count);

    // Cleanup
    json_object_put(json_array);

    return 0;
}