#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the input data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string into a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Check if the parsed object is an array
    if (json_obj != nullptr && json_object_is_type(json_obj, json_type_array)) {
        // Call the function-under-test
        size_t array_length = json_object_array_length(json_obj);
    }

    // Free the json_object
    if (json_obj != nullptr) {
        json_object_put(json_obj);
    }

    return 0;
}