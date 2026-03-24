#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Use FuzzedDataProvider to generate input data
    FuzzedDataProvider fuzzed_data(data, size);
    
    // Extract a string from the fuzzed data
    std::string input = fuzzed_data.ConsumeRandomLengthString(size);

    // Create a new JSON tokener
    struct json_tokener *tok = json_tokener_new();
    
    // Parse the fuzzed input
    if (tok != nullptr) {
        json_object *jobj = json_tokener_parse_ex(tok, input.c_str(), input.length());
        
        // Free the parsed JSON object if it was successfully created
        if (jobj != nullptr) {
            json_object_put(jobj);
        }

        // Clean up the tokener
        json_tokener_free(tok);
    }
    
    return 0;
}