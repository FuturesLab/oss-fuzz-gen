#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Call the function-under-test
    struct json_object *json_obj = json_object_new_array();

    // Use the json_object to ensure it's not optimized away
    if (json_obj != nullptr) {
        // Add elements to the json array if there is enough data
        while (fuzzed_data_provider.remaining_bytes() > 0) {
            // Consume a random length string from the fuzzed data
            std::string element = fuzzed_data_provider.ConsumeRandomLengthString(10);

            // Create a new json object string
            struct json_object *json_element = json_object_new_string(element.c_str());

            // Add the string object to the json array
            json_object_array_add(json_obj, json_element);
        }

        // Decrement the reference count of the json object
        json_object_put(json_obj);
    }

    return 0;
}