#include "fuzzer/FuzzedDataProvider.h"
#include <stdint.h>
#include <vector>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object from the remaining bytes
    std::vector<uint8_t> json_bytes = fuzzed_data.ConsumeRemainingBytes<uint8_t>();
    
    // Ensure the json_bytes vector is null-terminated for safe string conversion
    json_bytes.push_back('\0');
    
    struct json_object *jobj = json_tokener_parse(reinterpret_cast<const char*>(json_bytes.data()));

    // If parsing failed, return early
    if (jobj == nullptr) {
        return 0;
    }

    // Consume an int64_t value from the fuzzed data
    int64_t increment_value = fuzzed_data.ConsumeIntegral<int64_t>();

    // Check if the json_object is of integer type before calling json_object_int_inc
    if (json_object_is_type(jobj, json_type_int)) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of json_object_int_inc
        json_object_int_inc(jobj, JSON_C_OBJECT_ADD_CONSTANT_KEY);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    }

    // Decrement reference count to free the json_object
    json_object_put(jobj);

    return 0;
}