#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

// Include the correct headers for json-c functionality
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume the remaining bytes as a string to create a JSON object
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string to create a json_object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());

    // Ensure the json_object is not NULL
    if (jobj != NULL) {
        // Call the function-under-test
        struct lh_table *result = json_object_get_object(jobj);

        // Decrement the reference count of the json_object to free it
        json_object_put(jobj);
    }

    return 0;
}