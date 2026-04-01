#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string for the key
    std::string key = fuzzed_data.ConsumeRandomLengthString();

    // Consume remaining bytes for the JSON data
    std::vector<uint8_t> json_bytes = fuzzed_data.ConsumeRemainingBytes<uint8_t>();
    
    // Convert the JSON bytes to a string
    std::string json_str(reinterpret_cast<const char*>(json_bytes.data()), json_bytes.size());

    // Parse the JSON string into a json_object
    json_object *json_obj = json_tokener_parse(json_str.c_str());

    // Prepare the output json_object pointer
    json_object *result = nullptr;

    // Call the function-under-test
    json_object_object_get_ex(json_obj, key.c_str(), &result);

    // Clean up
    if (json_obj != nullptr) {
        json_object_put(json_obj);
    }

    return 0;
}