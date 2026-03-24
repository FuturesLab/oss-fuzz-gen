#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Create a FuzzedDataProvider to generate inputs
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new JSON object using the function-under-test
    struct json_object *new_obj = json_object_new_object();

    // Use the fuzzed data to add a string to the JSON object
    std::string key = fuzzed_data.ConsumeRandomLengthString(10);
    std::string value = fuzzed_data.ConsumeRandomLengthString(50);
    json_object_object_add(new_obj, key.c_str(), json_object_new_string(value.c_str()));

    // Clean up the allocated JSON object
    json_object_put(new_obj);

    return 0;
}