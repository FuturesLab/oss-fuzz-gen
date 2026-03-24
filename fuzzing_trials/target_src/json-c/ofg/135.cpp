#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data
    std::string input_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Ensure the string is null-terminated by using c_str()
    const char *c_str_input = input_string.c_str();

    // Call the function-under-test
    struct json_object *json_obj = json_object_new_string(c_str_input);

    // Clean up the json object if it was created
    if (json_obj != nullptr) {
        json_object_put(json_obj);
    }

    return 0;
}