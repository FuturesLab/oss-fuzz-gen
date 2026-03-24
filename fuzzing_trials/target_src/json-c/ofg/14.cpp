#include <cstddef>
#include <cstdint>
#include <string>
#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h> // Ensure you have the correct header for json_tokener

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tokener = json_tokener_new();

    // Check if tokener is successfully created
    if (tokener == nullptr) {
        return 0; // Exit if tokener creation failed
    }

    // Consume a portion of the data to simulate parsing
    size_t parse_length = fuzzed_data.ConsumeIntegralInRange<size_t>(0, size);
    std::string json_string = fuzzed_data.ConsumeRandomLengthString(parse_length);

    // Parse the JSON string using the tokener
    json_object *parsed_obj = json_tokener_parse_ex(tokener, json_string.c_str(), json_string.size());

    // Call the function-under-test
    enum json_tokener_error error = json_tokener_get_error(tokener);

    // Clean up
    if (parsed_obj != nullptr) {
        json_object_put(parsed_obj); // Decrement ref count and free if necessary
    }
    json_tokener_free(tokener);

    return 0;
}