#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the input data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string into a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // If parsing is successful, call the function-under-test
    if (json_obj != nullptr) {
        int result = json_object_get_string_len(json_obj);
        // Clean up the json_object
        json_object_put(json_obj);
    }

    return 0;
}