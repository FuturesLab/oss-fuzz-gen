#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a JSON object
    json_object *jobj = json_object_new_object();

    // Add an integer to the JSON object
    int64_t initial_value = fuzzed_data.ConsumeIntegral<int64_t>();
    json_object_object_add(jobj, "key", json_object_new_int64(initial_value));

    // Consume an int64_t value from the fuzzed data
    int64_t increment_value = fuzzed_data.ConsumeIntegral<int64_t>();

    // Call the function-under-test
    json_object_int_inc(jobj, increment_value);

    // Clean up
    json_object_put(jobj);

    return 0;
}