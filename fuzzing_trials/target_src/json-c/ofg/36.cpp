#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string to create a json_object
    struct json_object *jobj = json_tokener_parse(json_str.c_str());

    // Ensure the json_object is not NULL
    if (jobj != nullptr) {
        // Call the function-under-test
        int32_t result = json_object_get_int(jobj);

        // Clean up the json_object
        json_object_put(jobj);
    }

    return 0;
}