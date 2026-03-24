#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string>

// Include the correct json-c headers
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume a random length string from the fuzz data for the JSON input
    std::string json_input = fuzzed_data_provider.ConsumeRandomLengthString();

    // Prepare a variable for the error output
    enum json_tokener_error error;

    // Call the function-under-test
    struct json_object *result = json_tokener_parse_verbose(json_input.c_str(), &error);

    // If a JSON object was created, free it
    if (result != nullptr) {
        json_object_put(result);
    }

    return 0;
}