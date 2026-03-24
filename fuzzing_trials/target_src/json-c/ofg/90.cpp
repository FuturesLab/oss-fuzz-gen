#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a uint64_t value from the fuzzed data
    uint64_t value = fuzzed_data.ConsumeIntegral<uint64_t>();

    // Call the function-under-test with the fuzzed value
    struct json_object *json_obj = json_object_new_uint64(value);

    // Clean up the created json_object
    json_object_put(json_obj);

    return 0;
}