#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a boolean value from the fuzzed data
    json_bool bool_value = fuzzed_data.ConsumeBool();

    // Create a JSON object to be used as the first parameter
    struct json_object *json_obj = json_object_new_object();

    // Set a boolean value in the JSON object
    json_object_object_add(json_obj, "bool_key", json_object_new_boolean(bool_value));

    // Consume an integer value from the fuzzed data
    int32_t int_value = fuzzed_data.ConsumeIntegral<int32_t>();

    // Set an integer value in the JSON object
    json_object_object_add(json_obj, "int_key", json_object_new_int(int_value));

    // Consume a string value from the fuzzed data
    std::string string_value = fuzzed_data.ConsumeRandomLengthString();

    // Set a string value in the JSON object
    json_object_object_add(json_obj, "string_key", json_object_new_string(string_value.c_str()));

    // Free the JSON object to avoid memory leaks
    json_object_put(json_obj);

    return 0;
}