#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new json_object for the first parameter
    struct json_object *json_obj1 = json_object_new_object();

    // Consume a string for the second parameter
    std::string key = fuzzed_data.ConsumeRandomLengthString();
    const char *key_cstr = key.c_str();

    // Create a new json_object for the third parameter
    struct json_object *json_obj2 = json_object_new_object();

    // Call the function-under-test
    json_object_object_add(json_obj1, key_cstr, json_obj2);

    // Decrement reference counts to free the json objects
    json_object_put(json_obj1);
    json_object_put(json_obj2);

    return 0;
}