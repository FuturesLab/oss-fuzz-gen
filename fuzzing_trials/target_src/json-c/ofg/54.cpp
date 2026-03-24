#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the input data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the string into a JSON object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Check if the JSON object was successfully created
    if (json_obj != nullptr) {
        // Call the function-under-test
        const char *result = json_object_to_json_string(json_obj);

        // Free the JSON object
        json_object_put(json_obj);
    }

    return 0;
}