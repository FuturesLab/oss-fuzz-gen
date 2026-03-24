#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new JSON object
    json_object *jobj = json_object_new_object();

    // Populate the JSON object with some data
    while (fuzzed_data.remaining_bytes() > 0) {
        std::string key = fuzzed_data.ConsumeRandomLengthString(10);
        std::string value = fuzzed_data.ConsumeRandomLengthString(20);
        json_object *jstring = json_object_new_string(value.c_str());
        json_object_object_add(jobj, key.c_str(), jstring);
    }

    // Consume an integer for the second parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function under test
    const char *result = json_object_to_json_string_ext(jobj, flags);

    // Clean up
    json_object_put(jobj);

    return 0;
}