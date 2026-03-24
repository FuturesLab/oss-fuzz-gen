#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_types.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string for JSON data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString(1024);

    // Parse the JSON string to create a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());
    if (json_obj == nullptr) {
        return 0; // Return early if parsing fails
    }

    // Consume an integer to determine the json_type
    int json_type_int = fuzzed_data.ConsumeIntegralInRange<int>(0, json_type_null);

    // Cast to json_type
    json_type json_type_enum = static_cast<json_type>(json_type_int);

    // Call the function-under-test
    int result = json_object_is_type(json_obj, json_type_enum);

    // Clean up
    json_object_put(json_obj);

    return 0;
}