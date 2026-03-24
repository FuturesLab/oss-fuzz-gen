#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the data to create a JSON object
    std::string json_str = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string to create a json_object
    json_object *json_obj = json_tokener_parse(json_str.c_str());

    // Ensure the json_object is not NULL
    if (json_obj != nullptr) {
        // Call the function-under-test
        void *userdata = json_object_get_userdata(json_obj);

        // Free the json_object
        json_object_put(json_obj);
    }

    return 0;
}