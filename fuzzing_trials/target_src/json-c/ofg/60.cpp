#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume a string from the fuzzed data
    std::string json_string = fuzzed_data_provider.ConsumeRemainingBytesAsString();

    // Parse the JSON string into a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // If parsing was successful, call the function-under-test
    if (json_obj != nullptr) {
        int64_t result = json_object_get_int64(json_obj);

        // Clean up the json_object
        json_object_put(json_obj);
    }

    return 0;
}