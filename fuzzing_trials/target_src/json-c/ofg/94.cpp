#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the provided data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

    // Parse the JSON string using json_tokener_parse
    struct json_object *parsed_json = json_tokener_parse(json_string.c_str());

    // Clean up the parsed JSON object
    if (parsed_json != nullptr) {
        json_object_put(parsed_json);
    }

    return 0;
}