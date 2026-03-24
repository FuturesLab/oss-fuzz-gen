#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string to create a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // If json_obj is NULL, we cannot proceed with json_object_get
    if (json_obj == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct json_object *result = json_object_get(json_obj);

    // Decrement the reference count for the original json_obj
    json_object_put(json_obj);

    // Decrement the reference count for the result from json_object_get
    json_object_put(result);

    return 0;
}