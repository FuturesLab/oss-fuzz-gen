#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_str = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string into a json_object
    struct json_object *jobj = json_tokener_parse(json_str.c_str());

    // Check if the json_object is not NULL before calling the function
    if (jobj != NULL) {
        // Call the function-under-test
        json_bool result = json_object_get_boolean(jobj);

        // To avoid memory leaks, free the json_object
        json_object_put(jobj);
    }

    return 0;
}