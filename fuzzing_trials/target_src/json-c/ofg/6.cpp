#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tokener = json_tokener_new();
    if (!tokener) {
        return 0; // If tokener creation fails, exit early
    }

    // Consume a string from the data
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();
    const char *json_cstr = json_str.c_str();
    int json_len = static_cast<int>(json_str.size());

    // Call the function-under-test
    struct json_object *result = json_tokener_parse_ex(tokener, json_cstr, json_len);

    // Cleanup
    if (result) {
        json_object_put(result);
    }
    json_tokener_free(tokener);

    return 0;
}