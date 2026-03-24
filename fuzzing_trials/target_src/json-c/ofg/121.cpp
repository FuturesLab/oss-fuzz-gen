#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"  // Include the header for json_tokener_parse
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    struct json_object *json_obj = json_object_new_object();

    // Consume an int64_t value from the fuzzed data
    int64_t int_value = fuzzed_data.ConsumeIntegral<int64_t>();

    // Add an integer to the JSON object
    json_object_object_add(json_obj, "int_key", json_object_new_int64(int_value));

    // Consume a string from the fuzzed data
    std::string str_value = fuzzed_data.ConsumeRandomLengthString(100);
    json_object_object_add(json_obj, "str_key", json_object_new_string(str_value.c_str()));

    // Consume a boolean value from the fuzzed data
    bool bool_value = fuzzed_data.ConsumeBool();
    json_object_object_add(json_obj, "bool_key", json_object_new_boolean(bool_value));

    // Serialize the JSON object to a string
    const char *json_str = json_object_to_json_string(json_obj);

    // Parse the JSON string back into a new JSON object
    struct json_object *parsed_json_obj = json_tokener_parse(json_str);

    // Clean up
    json_object_put(json_obj);
    json_object_put(parsed_json_obj);

    return 0;
}