#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <string>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Extract an int64_t value from the fuzzed data
    int64_t int64_value = fuzzed_data.ConsumeIntegral<int64_t>();

    // Call the function-under-test
    struct json_object *json_obj = json_object_new_int64(int64_value);

    // Additional operations to increase code coverage
    if (json_obj != nullptr) {
        // Convert the JSON object to a string
        const char *json_str = json_object_to_json_string(json_obj);

        // Perform some string operations
        if (json_str != nullptr) {
            std::string json_cpp_str(json_str);
            // Manipulate the string to further test the library
            json_cpp_str.append("_test");
            json_cpp_str.find("test");
        }

        // Clean up the json_object to avoid memory leaks
        json_object_put(json_obj);
    }

    return 0;
}