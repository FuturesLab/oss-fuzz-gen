#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object to pass as the first argument
    struct json_object *json_obj = json_object_new_object();

    // Consume an integer from the fuzzed data to pass as the second argument
    int int_value = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_object_set_int(json_obj, int_value);

    // Clean up
    json_object_put(json_obj);

    return 0;
}