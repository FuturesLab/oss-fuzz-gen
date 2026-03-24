#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <string>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Call the function-under-test
    struct json_object *json_array = json_object_new_array();

    // Use the fuzzed data to add elements to the JSON array
    while (fuzzed_data.remaining_bytes() > 0) {
        // Randomly decide to add either an integer or a string
        if (fuzzed_data.ConsumeBool()) {
            // Add an integer
            int value = fuzzed_data.ConsumeIntegral<int>();
            json_object_array_add(json_array, json_object_new_int(value));
        } else {
            // Add a string
            std::string str = fuzzed_data.ConsumeRandomLengthString();
            json_object_array_add(json_array, json_object_new_string(str.c_str()));
        }
    }

    // Clean up the created JSON object
    if (json_array != nullptr) {
        json_object_put(json_array);
    }

    return 0;
}