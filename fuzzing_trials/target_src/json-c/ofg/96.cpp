#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string to simulate a JSON input
    std::string json_str = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string into a json_object
    json_object *jobj = json_tokener_parse(json_str.c_str());

    // Ensure the json_object is valid
    if (jobj != nullptr) {
        // Call the function-under-test
        uint64_t result = json_object_get_uint64(jobj);

        // Clean up the json_object
        json_object_put(jobj);
    }

    return 0;
}