#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tokener = json_tokener_new();
    if (!tokener) {
        return 0; // If creation fails, return early
    }

    // Consume a random length JSON string from the input data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string using the tokener
    json_object *jobj = json_tokener_parse_ex(tokener, json_string.c_str(), json_string.size());

    // Call the function-under-test
    size_t parse_end = json_tokener_get_parse_end(tokener);

    // Clean up
    if (jobj) {
        json_object_put(jobj); // Decrement reference count and free if necessary
    }
    json_tokener_free(tokener);

    return 0;
}