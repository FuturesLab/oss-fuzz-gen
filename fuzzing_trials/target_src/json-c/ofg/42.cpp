#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tokener = json_tokener_new();

    // Ensure the tokener is not NULL
    if (tokener == nullptr) {
        return 0;
    }

    // Convert the input data to a string to feed into json_tokener_parse_ex
    std::string input_str = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the input string using the json_tokener
    struct json_object *parsed_json = json_tokener_parse_ex(tokener, input_str.c_str(), input_str.length());

    // Free the json_tokener object
    json_tokener_free(tokener);

    // If parsing was successful, free the parsed json object
    if (parsed_json != nullptr) {
        json_object_put(parsed_json);
    }

    return 0;
}