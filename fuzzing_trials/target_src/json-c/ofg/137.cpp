#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider to consume fuzzing input
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tokener = json_tokener_new();
    if (tokener == nullptr) {
        return 0; // If creation fails, exit early
    }

    // Consume an integer for the flags parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Set flags for the tokener
    json_tokener_set_flags(tokener, flags);

    // Attempt to parse the input data as JSON
    const char* json_data = reinterpret_cast<const char*>(data);
    struct json_object *parsed_json = json_tokener_parse_ex(tokener, json_data, size);

    // Clean up
    if (parsed_json != nullptr) {
        json_object_put(parsed_json); // Decrease reference count and free if needed
    }
    json_tokener_free(tokener);

    return 0;
}