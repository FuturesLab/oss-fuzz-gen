#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();
    
    // Ensure the consumed string is not empty
    if (json_string.empty()) {
        return 0;
    }

    json_object *jobj = json_tokener_parse(json_string.c_str());

    // Consume an integer for the flags parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Ensure json_object is not NULL
    if (jobj != nullptr) {
        // Call the function-under-test
        const char *result = json_object_to_json_string_ext(jobj, flags);
        
        // Clean up
        json_object_put(jobj);
    }

    return 0;
}