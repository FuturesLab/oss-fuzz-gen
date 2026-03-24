#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <cstdio>  // Include for printf

// Include the necessary json-c headers
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/json_util.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Generate a string input for JSON processing
    std::string json_input = fuzzed_data.ConsumeRandomLengthString();

    // Attempt to parse the JSON input
    json_object *parsed_json = json_tokener_parse(json_input.c_str());

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