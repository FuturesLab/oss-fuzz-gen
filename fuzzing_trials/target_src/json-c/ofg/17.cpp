#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the provided data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a boolean value for the json_bool parameter
    json_bool bool_value = fuzzed_data.ConsumeBool();

    // Create a JSON object
    struct json_object *json_obj = json_object_new_object();

    // Ensure the JSON object is not null
    if (json_obj == NULL) {
        return 0;
    }

    // Create a key for the JSON object
    std::string key = fuzzed_data.ConsumeRandomLengthString(10);

    // Add a boolean value to the JSON object with the generated key
    json_object_object_add(json_obj, key.c_str(), json_object_new_boolean(bool_value));

    // Optionally, serialize the JSON object to a string to increase code coverage
    const char *json_str = json_object_to_json_string(json_obj);

    // Free the JSON object
    json_object_put(json_obj);

    return 0;
}