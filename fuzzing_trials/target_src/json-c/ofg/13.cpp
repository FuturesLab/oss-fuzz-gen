#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <string>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string to create a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Check if parsing was successful
    if (json_obj != nullptr) {
        // Call the function-under-test
        const char *result = json_object_get_string(json_obj);

        // Free the json_object
        json_object_put(json_obj);
    }

    return 0;
}