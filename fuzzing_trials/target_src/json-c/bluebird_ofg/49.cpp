#include "fuzzer/FuzzedDataProvider.h"
#include <string>
#include <cstdint>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to avoid consuming more than available
    if (size == 0) {
        return 0; // Exit early if there's no data to process
    }

    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Ensure there is enough data to consume a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0; // Exit early if not enough data
    }

    // Consume a uint64_t value from the fuzzed data
    uint64_t value = fuzzed_data_provider.ConsumeIntegral<uint64_t>();

    // Create a JSON object from the uint64_t value
    struct json_object *json_obj = json_object_new_object();
    if (json_obj == nullptr) {
        return 0; // Exit if the JSON object creation failed
    }

    struct json_object *value_obj = json_object_new_uint64(value);
    if (value_obj == nullptr) {
        json_object_put(json_obj);
        return 0; // Exit if the JSON object creation failed
    }
    json_object_object_add(json_obj, "uint64_value", value_obj);

    // Consume a string from the fuzzed data
    std::string str = fuzzed_data_provider.ConsumeRandomLengthString(size - sizeof(uint64_t));

    // Add the string as a new field in the JSON object
    struct json_object *str_obj = json_object_new_string(str.c_str());
    if (str_obj == nullptr) {
        json_object_put(json_obj);
        return 0; // Exit if the JSON object creation failed
    }
    json_object_object_add(json_obj, "string_value", str_obj);

    // Consume a boolean value from the fuzzed data
    bool bool_value = fuzzed_data_provider.ConsumeBool();

    // Add the boolean as a new field in the JSON object
    struct json_object *bool_obj = json_object_new_boolean(bool_value);
    if (bool_obj == nullptr) {
        json_object_put(json_obj);
        return 0; // Exit if the JSON object creation failed
    }
    json_object_object_add(json_obj, "bool_value", bool_obj);

    // Clean up the json_object to prevent memory leaks
    json_object_put(json_obj);

    return 0;
}