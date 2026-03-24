#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"  // Correct path for the json_object_new_double_s function
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Extract a double value from the fuzzed data
    double double_value = fuzzed_data_provider.ConsumeFloatingPoint<double>();

    // Extract a string from the fuzzed data
    std::string string_value = fuzzed_data_provider.ConsumeRandomLengthString(100);

    // Call the function-under-test
    struct json_object *obj = json_object_new_double_s(double_value, string_value.c_str());

    // Clean up the created json_object
    if (obj != NULL) {
        json_object_put(obj);
    }

    return 0;
}