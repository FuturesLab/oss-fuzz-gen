#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string to create a json_object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());

    // Check if the json_object was successfully created
    if (jobj != nullptr) {
        // Call the function-under-test
        json_type type = json_object_get_type(jobj);

        // Free the json_object
        json_object_put(jobj);
    }

    return 0;
}