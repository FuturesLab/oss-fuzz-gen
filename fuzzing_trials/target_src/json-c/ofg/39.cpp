#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Prepare the first json_object
    std::string json_str1 = fuzzed_data.ConsumeRandomLengthString(size / 2);
    struct json_object *json_obj1 = json_tokener_parse(json_str1.c_str());
    if (json_obj1 == nullptr) {
        return 0; // If parsing fails, exit early
    }

    // Prepare the second json_object
    std::string json_str2 = fuzzed_data.ConsumeRandomLengthString(size / 2);
    struct json_object *json_obj2 = json_tokener_parse(json_str2.c_str());
    if (json_obj2 == nullptr) {
        json_object_put(json_obj1); // Clean up
        return 0; // If parsing fails, exit early
    }

    // Compare the two json_objects using json_object_equal
    int are_equal = json_object_equal(json_obj1, json_obj2);

    // Clean up
    json_object_put(json_obj1);
    json_object_put(json_obj2);

    return 0;
}