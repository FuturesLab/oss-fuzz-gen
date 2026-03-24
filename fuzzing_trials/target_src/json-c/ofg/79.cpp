#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Create a FuzzedDataProvider to handle the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the string into a json_object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());
    
    // If parsing was successful, call the function-under-test
    if (jobj != nullptr) {
        double result = json_object_get_double(jobj);

        // Clean up the json_object
        json_object_put(jobj);
    }

    return 0;
}