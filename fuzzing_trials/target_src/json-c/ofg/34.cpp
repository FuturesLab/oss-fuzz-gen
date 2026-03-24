#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the fuzzing input
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object to pass to the function-under-test
    json_object *json_obj = json_object_new_object();
    if (json_obj == nullptr) {
        return 0; // If json_object creation fails, exit early
    }

    // Consume a double value from the fuzzed data
    double double_value = fuzzed_data.ConsumeFloatingPoint<double>();

    // Call the function-under-test
    json_object_set_double(json_obj, double_value);

    // Decrement reference count of json_obj to avoid memory leak
    json_object_put(json_obj);

    return 0;
}