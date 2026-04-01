#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    struct json_object *jobj = json_object_new_object();

    // Consume a uint64_t value from the fuzzed data
    uint64_t value = fuzzed_data.ConsumeIntegral<uint64_t>();

    // Call the function-under-test
    json_object_set_uint64(jobj, value);

    // Clean up
    json_object_put(jobj);

    return 0;
}