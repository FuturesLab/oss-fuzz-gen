#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a portion of the input data to create a json_object
    std::string json_str = fuzzed_data.ConsumeRandomLengthString(size);
    struct json_object *json_obj = json_tokener_parse(json_str.c_str());
    
    // If json_obj is NULL, return early
    if (!json_obj) {
        return 0;
    }

    // Create another json_object to insert
    std::string json_str2 = fuzzed_data.ConsumeRandomLengthString(size);
    struct json_object *json_obj2 = json_tokener_parse(json_str2.c_str());

    // If json_obj2 is NULL, clean up and return early
    if (!json_obj2) {
        json_object_put(json_obj);
        return 0;
    }

    // Consume an index value
    size_t index = fuzzed_data.ConsumeIntegral<size_t>();

    // Call the function-under-test
    json_object_array_insert_idx(json_obj, index, json_obj2);

    // Clean up
    json_object_put(json_obj);
    json_object_put(json_obj2);

    return 0;
}