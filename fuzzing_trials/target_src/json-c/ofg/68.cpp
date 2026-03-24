#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a double value from the fuzzed data
    double double_value = fuzzed_data.ConsumeFloatingPoint<double>();

    // Call the function-under-test with the fuzzed double value
    struct json_object *json_obj = json_object_new_double(double_value);

    // Clean up the created json_object to avoid memory leaks
    json_object_put(json_obj);

    return 0;
}