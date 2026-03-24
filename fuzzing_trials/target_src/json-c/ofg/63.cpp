#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the provided data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the data to create a json_object
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();
    
    // Parse the string into a json_object
    struct json_object *jobj = json_tokener_parse(json_string.c_str());

    // Check if parsing was successful
    if (jobj == nullptr) {
        return 0; // Early exit if parsing failed
    }

    // Consume an integer from the remaining data
    int int_value = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_object_set_int(jobj, int_value);

    // Decrement the reference count of the json_object to prevent memory leaks
    json_object_put(jobj);

    return 0;
}