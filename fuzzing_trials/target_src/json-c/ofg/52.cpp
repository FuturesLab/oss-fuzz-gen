#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with provided data and size
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume a random length string from the fuzzing data to create a JSON object
    std::string json_string = fuzzed_data_provider.ConsumeRandomLengthString();
    
    // Parse the JSON string to create a json_object
    json_object *jobj = json_tokener_parse(json_string.c_str());

    // Ensure that the json_object is not NULL
    if (jobj != nullptr) {
        // Call the function-under-test
        void *userdata = json_object_get_userdata(jobj);

        // Clean up the json_object
        json_object_put(jobj);
    }

    return 0;
}