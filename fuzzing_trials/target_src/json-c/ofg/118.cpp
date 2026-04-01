#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a boolean value from the fuzzed data
    json_bool bool_value = fuzzed_data.ConsumeBool();

    // Call the function-under-test with the consumed boolean value
    struct json_object *bool_obj = json_object_new_boolean(bool_value);

    // Consume a string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the string into a JSON object
    struct json_object *parsed_obj = json_tokener_parse(json_string.c_str());

    // If parsing was successful, manipulate the JSON object
    if (parsed_obj != nullptr) {
        // Get the type of the JSON object
        json_type type = json_object_get_type(parsed_obj);

        // Perform operations based on the JSON type
        switch (type) {
            case json_type_object:
                json_object_object_add(parsed_obj, "new_key", bool_obj);
                break;
            case json_type_array:
                json_object_array_add(parsed_obj, bool_obj);
                break;
            default:
                // For other types, just put the boolean object
                json_object_put(bool_obj);
                break;
        }
    } else {
        // If parsing failed, just put the boolean object
        json_object_put(bool_obj);
    }

    // Free the created json_object to avoid memory leaks
    json_object_put(parsed_obj);

    return 0;
}