#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data for the JSON object key
    std::string json_key = fuzzed_data.ConsumeRandomLengthString();

    // Create a new JSON object
    struct json_object *jobj = json_object_new_object();

    // Add the key to the JSON object with a default value
    json_object_object_add(jobj, json_key.c_str(), json_object_new_int64(0));

    // Consume an int64_t value from the fuzzed data
    int64_t value = fuzzed_data.ConsumeIntegral<int64_t>();

    // Call the function-under-test
    json_object_set_int64(jobj, value);

    // Decrement the reference count of the JSON object
    json_object_put(jobj);

    return 0;
}