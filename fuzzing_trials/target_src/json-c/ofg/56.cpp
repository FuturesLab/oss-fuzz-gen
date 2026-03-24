#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume an integer for the json_object_new_array_ext function
    int array_size = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    struct json_object *json_array = json_object_new_array_ext(array_size);

    // Clean up the created JSON object to prevent memory leaks
    if (json_array != nullptr) {
        json_object_put(json_array);
    }

    return 0;
}