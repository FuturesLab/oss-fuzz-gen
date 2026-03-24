#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new JSON object
    struct json_object *jobj = json_object_new_object();

    // Consume a uint64_t value from the fuzzed data
    uint64_t value = fuzzed_data.ConsumeIntegral<uint64_t>();

    // Call the function-under-test
    json_object_set_uint64(jobj, value);

    // Decrement the reference count for the JSON object
    json_object_put(jobj);

    return 0;
}