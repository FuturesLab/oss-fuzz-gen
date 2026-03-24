#include "fuzzer/FuzzedDataProvider.h"
#include <string>
#include <cstdio>  // Include for printf

// Include the necessary json-c headers
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h"

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Generate a string input for JSON processing
    std::string json_input = fuzzed_data.ConsumeRandomLengthString();

    // Attempt to parse the JSON input

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function json_tokener_parse with json_object_from_file
    json_object *parsed_json = json_object_from_file(json_input.c_str());
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Check for parsing errors
    const char *error_message = json_util_get_last_err();
    if (error_message != nullptr) {
        // Print the error message if parsing failed
        printf("Error message: %s\n", error_message);
    }

    // Clean up the parsed JSON object if it was successfully created
    if (parsed_json != nullptr) {
        json_object_put(parsed_json);
    }

    return 0;
}