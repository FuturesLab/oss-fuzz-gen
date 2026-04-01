#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    json_object *jobj = json_object_new_object();
    if (jobj == nullptr) {
        return 0; // Early return if json_object creation fails
    }

    // Consume a string from the fuzzed data
    std::string str = fuzzed_data.ConsumeRandomLengthString(100);
    const char *c_str = str.c_str();

    // Consume an integer for the length
    int len = fuzzed_data.ConsumeIntegralInRange<int>(0, str.size());

    // Call the function-under-test
    json_object_set_string_len(jobj, c_str, len);

    // Clean up the json_object
    json_object_put(jobj);

    return 0;
}