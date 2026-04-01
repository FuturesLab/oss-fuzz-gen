#include "fuzzer/FuzzedDataProvider.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a portion of data to create a JSON string
    std::string json_str = fuzzed_data.ConsumeRandomLengthString(size);

    // Parse the JSON string to create a json_object
    struct json_object *jobj = json_tokener_parse(json_str.c_str());
    if (jobj == nullptr || !json_object_is_type(jobj, json_type_array)) {
        json_object_put(jobj); // Clean up if parsing fails or it's not an array
        return 0; // If parsing fails or it's not an array, exit early
    }

    // Consume an integer for the second parameter
    int shrink_size = fuzzed_data.ConsumeIntegralInRange<int>(0, json_object_array_length(jobj));

    // Call the function-under-test
    json_object_array_shrink(jobj, shrink_size);

    // Clean up
    json_object_put(jobj);

    return 0;
}