#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tok = json_tokener_new();

    // Ensure tokener is not NULL
    if (tok == nullptr) {
        return 0;
    }

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string
    json_object *jobj = json_tokener_parse_ex(tok, json_string.c_str(), json_string.size());

    // Call the function-under-test
    json_tokener_error error = json_tokener_get_error(tok);

    // Clean up
    if (jobj != nullptr) {
        json_object_put(jobj);
    }
    json_tokener_free(tok);

    return 0;
}