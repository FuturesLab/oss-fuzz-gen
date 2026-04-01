#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);
    
    // Create a json_object
    json_object *jobj = json_object_new_object();
    
    // Consume a random length string from the fuzzed data
    std::string random_string = fuzzed_data.ConsumeRandomLengthString();
    
    // Ensure the string is null-terminated and non-empty
    const char *c_str = random_string.c_str();
    
    // Call the function-under-test
    json_object_object_add(jobj, "key", json_object_new_string(c_str));
    
    // Clean up
    json_object_put(jobj);
    
    return 0;
}