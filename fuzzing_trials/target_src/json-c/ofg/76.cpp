#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length of bytes to create the first JSON string
    std::string json_str1 = fuzzed_data.ConsumeRandomLengthString();
    // Consume the remaining bytes to create the second JSON string
    std::string json_str2 = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON strings into json_object
    struct json_object *json_obj1 = json_tokener_parse(json_str1.c_str());
    struct json_object *json_obj2 = json_tokener_parse(json_str2.c_str());

    // Ensure that both json_objects are not NULL before calling the function
    if (json_obj1 != NULL && json_obj2 != NULL) {
        // Call the function-under-test
        int result = json_object_equal(json_obj1, json_obj2);
    }

    // Free the json_objects
    if (json_obj1 != NULL) {
        json_object_put(json_obj1);
    }
    if (json_obj2 != NULL) {
        json_object_put(json_obj2);
    }

    return 0;
}