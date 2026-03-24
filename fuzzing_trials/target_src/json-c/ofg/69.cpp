#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Extract a double value from the fuzzed data
    double double_value = fuzzed_data.ConsumeFloatingPoint<double>();

    // Call the function-under-test with the extracted double value
    struct json_object *json_obj = json_object_new_double(double_value);

    // Clean up the created json_object
    json_object_put(json_obj);

    return 0;
}