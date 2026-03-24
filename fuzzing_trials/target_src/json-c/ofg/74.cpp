#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string to create a json_object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());

    // If the json_object is successfully created, call the function-under-test
    if (jobj != nullptr) {
        json_bool result = json_object_get_boolean(jobj);
        // Clean up the json_object
        json_object_put(jobj);
    }

    return 0;
}