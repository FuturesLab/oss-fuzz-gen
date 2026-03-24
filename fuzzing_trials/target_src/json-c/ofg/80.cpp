#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Generate a JSON string from the fuzzed data
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string into a json_object
    struct json_object *json_obj = json_tokener_parse(json_str.c_str());

    // If parsing was successful, call the function-under-test
    if (json_obj != nullptr) {
        double result = json_object_get_double(json_obj);
        // Use the result in some way to avoid compiler optimizations
        (void)result;

        // Free the json_object
        json_object_put(json_obj);
    }

    return 0;
}