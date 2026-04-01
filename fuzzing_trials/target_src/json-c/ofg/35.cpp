#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new JSON object
    struct json_object *json_obj = json_object_new_object();
    if (!json_obj) {
        return 0; // Return if the object creation fails
    }

    // Consume a double value from the fuzzed data
    double value = fuzzed_data.ConsumeFloatingPoint<double>();

    // Call the function-under-test
    json_object_set_double(json_obj, value);

    // Decrement the reference count of the JSON object
    json_object_put(json_obj);

    return 0;
}