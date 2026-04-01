#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_types.h"

// Define the maximum value for the json_type enum
constexpr int JSON_TYPE_MAX_VALUE = json_type_string;

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Ensure the json_obj is not NULL
    if (json_obj == NULL) {
        return 0;
    }

    // Consume an integer within the range of json_type enumeration
    json_type json_type_value = static_cast<json_type>(
        fuzzed_data.ConsumeIntegralInRange<int>(0, JSON_TYPE_MAX_VALUE)
    );

    // Call the function-under-test
    int result = json_object_is_type(json_obj, json_type_value);

    // Clean up the JSON object
    json_object_put(json_obj);

    return 0;
}