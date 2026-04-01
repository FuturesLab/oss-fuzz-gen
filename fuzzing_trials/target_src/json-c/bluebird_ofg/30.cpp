#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    struct json_object *jobj = json_object_new_object();

    // Consume a string from the fuzzed data to use as a key

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_new_object to json_object_object_add
    struct json_object* ret_json_object_new_int64_ihecf = json_object_new_int64(JSON_C_TO_STRING_NOZERO);
    if (ret_json_object_new_int64_ihecf == NULL){
    	return 0;
    }

    int ret_json_object_object_add_srllf = json_object_object_add(jobj, (const char *)"w", ret_json_object_new_int64_ihecf);
    if (ret_json_object_object_add_srllf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    std::string key = fuzzed_data.ConsumeRandomLengthString();

    // Ensure the key is not empty
    if (!key.empty()) {
        // Add a dummy entry to the json_object to ensure the key exists
        json_object_object_add(jobj, key.c_str(), json_object_new_string("dummy_value"));

        // Call the function-under-test
        json_object_object_del(jobj, key.c_str());
    }

    // Clean up the json_object
    json_object_put(jobj);

    return 0;
}