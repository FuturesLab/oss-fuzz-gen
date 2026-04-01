#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    struct json_object *jobj = json_object_new_object();

    // Consume a string from the fuzzed data to use as a key
    std::string key = fuzzed_data.ConsumeRandomLengthString();

    // Ensure the key is not empty
    if (!key.empty()) {
        // Add a dummy entry to the json_object to ensure the key exists
        json_object_object_add(jobj, key.c_str(), json_object_new_string("dummy_value"));

        // Call the function-under-test
        json_object_object_del(jobj, key.c_str());
    }

    // Clean up the json_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_object_del to json_object_int_inc
        int ret_json_object_object_length_utmpx = json_object_object_length(jobj);
        if (ret_json_object_object_length_utmpx < 0){
        	return 0;
        }

        int ret_json_object_int_inc_hewvr = json_object_int_inc(jobj, (int64_t )ret_json_object_object_length_utmpx);
        if (ret_json_object_int_inc_hewvr < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_int_inc to json_object_set_int

        int ret_json_object_set_int_vinbv = json_object_set_int(jobj, JSON_C_TO_STRING_SPACED);
        if (ret_json_object_set_int_vinbv < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    json_object_put(jobj);

    return 0;
}