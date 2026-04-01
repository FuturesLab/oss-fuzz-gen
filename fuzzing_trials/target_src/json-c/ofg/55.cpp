#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the input data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();
    
    // Parse the string into a JSON object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    if (json_obj != NULL) {
        // Call the function-under-test
        const char *result = json_object_to_json_string(json_obj);

        // Free the JSON object
        json_object_put(json_obj);
    }

    return 0;
}