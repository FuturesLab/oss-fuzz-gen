#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a double value from the fuzzed data
    double double_value = fuzzed_data.ConsumeFloatingPoint<double>();

    // Consume a string from the fuzzed data
    std::string str = fuzzed_data.ConsumeRemainingBytesAsString();

    // Call the function-under-test with the fuzzed inputs
    struct json_object *result = json_object_new_double_s(double_value, str.c_str());

    // Clean up the json_object if it's not NULL
    if (result != NULL) {
        json_object_put(result);
    }

    return 0;
}