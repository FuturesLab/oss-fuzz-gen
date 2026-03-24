#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a JSON object from a string
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // If the JSON object couldn't be created, return early
    if (!json_obj) {
        return 0;
    }

    // Consume an integer for the flags parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Prepare a size_t variable for the length
    size_t length = 0;

    // Call the function-under-test
    const char *result = json_object_to_json_string_length(json_obj, flags, &length);

    // Clean up the JSON object
    json_object_put(json_obj);

    return 0;
}