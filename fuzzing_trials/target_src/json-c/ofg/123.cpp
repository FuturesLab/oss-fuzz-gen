#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume a random length string from the data
    std::string json_string = fuzzed_data_provider.ConsumeRemainingBytesAsString();

    // Prepare the json_tokener_error variable
    enum json_tokener_error error;

    // Call the function-under-test
    struct json_object *result = json_tokener_parse_verbose(json_string.c_str(), &error);

    // Clean up the json_object if it was successfully created
    if (result != nullptr) {
        json_object_put(result);
    }

    return 0;
}