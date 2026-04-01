#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_tokener object
    struct json_tokener *tokener = json_tokener_new();
    if (tokener == nullptr) {
        return 0; // Early exit if json_tokener_new fails
    }

    // Consume an integer for the flags parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Set the flags for the tokener
    json_tokener_set_flags(tokener, flags);

    // Use the remaining data as input for json_tokener_parse_ex
    const char *json_data = reinterpret_cast<const char*>(fuzzed_data.ConsumeRemainingBytes<uint8_t>().data());
    size_t json_data_len = fuzzed_data.remaining_bytes();

    // Call the function-under-test
    json_object *parsed_json = json_tokener_parse_ex(tokener, json_data, json_data_len);

    // Clean up
    if (parsed_json != nullptr) {
        json_object_put(parsed_json); // Free the parsed JSON object
    }
    json_tokener_free(tokener);

    return 0;
}