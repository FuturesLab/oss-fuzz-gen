#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdlib>
#include <string>

// Include the correct headers from the json-c library
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data to be used as JSON input
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string into a json_object
    struct json_object *jobj = json_tokener_parse(json_str.c_str());

    // If parsing was successful, call the function-under-test
    if (jobj != nullptr) {
        int64_t result = json_object_get_int64(jobj);
        // Use the result in some way to prevent compiler optimizations
        (void)result; // Cast to void to suppress unused variable warning

        // Decrement the reference count of the json_object
        json_object_put(jobj);
    }

    return 0;
}