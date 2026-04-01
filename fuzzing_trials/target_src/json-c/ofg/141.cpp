#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Initialize a json_tokener object
    struct json_tokener *tokener = json_tokener_new();
    if (!tokener) {
        return 0; // If initialization fails, return early
    }

    // Optionally, you can use fuzzed data to set some properties of the tokener
    // For example, you could fuzz the depth of the tokener
    int depth = fuzzed_data.ConsumeIntegralInRange<int>(0, 32);
    tokener->max_depth = depth;

    // Attempt to parse the input data as JSON
    enum json_tokener_error jerr;
    struct json_object *jobj = json_tokener_parse_ex(tokener, reinterpret_cast<const char*>(data), size);

    // Check if parsing was successful
    jerr = json_tokener_get_error(tokener);
    if (jerr == json_tokener_success) {
        // Successfully parsed JSON object
        json_object_put(jobj); // Decrement reference count and free if necessary
    }

    // Clean up
    json_tokener_free(tokener);

    return 0;
}