#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Create a FuzzedDataProvider instance
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data to initialize a json_object
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the string into a json_object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());
    
    // Check if the json_object was successfully created
    if (jobj != nullptr) {
        // Call the function-under-test
        json_type type = json_object_get_type(jobj);

        // Decrement the reference count of the json_object
        json_object_put(jobj);
    }

    return 0;
}