#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h" // Include the header for json_tokener_parse

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data.
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume an int64_t value from the fuzzed data.
    int64_t int64_value = fuzzed_data.ConsumeIntegral<int64_t>();

    // Call the function-under-test with the fuzzed int64_t value.
    struct json_object *result = json_object_new_int64(int64_value);

    // Additional operations to increase code coverage:
    // Convert the json_object to a string and back to an int64
    const char *json_str = json_object_to_json_string(result);
    struct json_object *parsed_result = json_tokener_parse(json_str);

    // Verify the parsed result is the same as the original
    if (parsed_result != NULL) {
        // Directly get the int64 value from the json_object
        int64_t parsed_value = json_object_get_int64(parsed_result);

        // Compare the parsed value with the original value
        if (parsed_value != int64_value) {
            // Handle unexpected result
            json_object_put(parsed_result);
            json_object_put(result);
            return 1;
        }

        // Clean up the parsed json_object
        json_object_put(parsed_result);
    }

    // Clean up the original json_object to prevent memory leaks.
    json_object_put(result);

    return 0;
}