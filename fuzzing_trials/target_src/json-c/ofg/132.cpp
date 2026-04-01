#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume an integer from the fuzzed data
    int32_t int_value = fuzzed_data.ConsumeIntegral<int32_t>();
    
    // Consume a boolean from the fuzzed data
    bool bool_value = fuzzed_data.ConsumeBool();
    
    // Consume a string from the fuzzed data
    std::string string_value = fuzzed_data.ConsumeRandomLengthString();

    // Create a JSON object and populate it with various types
    struct json_object *json_obj = json_object_new_object();
    struct json_object *int_json = json_object_new_int(int_value);
    struct json_object *bool_json = json_object_new_boolean(bool_value);
    struct json_object *string_json = json_object_new_string(string_value.c_str());

    // Add the JSON elements to the JSON object
    json_object_object_add(json_obj, "int", int_json);
    json_object_object_add(json_obj, "bool", bool_json);
    json_object_object_add(json_obj, "string", string_json);

    // Serialize the JSON object to a string
    const char *json_str = json_object_to_json_string(json_obj);

    // Optionally print the JSON string for debugging (commented out in fuzzing)
    // printf("%s\n", json_str);

    // Clean up the created json_object
    json_object_put(json_obj);

    return 0;
}