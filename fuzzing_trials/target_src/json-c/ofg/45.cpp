#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    json_object *jobj = json_object_new_object();
    if (jobj == nullptr) {
        return 0; // If object creation fails, exit early
    }

    // Consume a string from the fuzzed data
    std::string key = fuzzed_data.ConsumeRandomLengthString(50);
    const char *key_cstr = key.c_str();

    // Consume another string from the fuzzed data
    std::string value = fuzzed_data.ConsumeRandomLengthString(100);
    const char *value_cstr = value.c_str();

    // Consume an integer for the length
    int length = fuzzed_data.ConsumeIntegralInRange<int>(0, value.size());

    // Call the function-under-test
    json_object_set_string_len(jobj, key_cstr, length);

    // Decrement reference count for json_object
    json_object_put(jobj);

    return 0;
}