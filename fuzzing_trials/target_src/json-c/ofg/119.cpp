#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h" // Correct path for json_object functions
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new JSON object
    json_object *jobj = json_object_new_object();
    if (jobj == nullptr) {
        return 0; // Return early if object creation fails
    }

    // Consume a string from the fuzzed data
    std::string str = fuzzed_data.ConsumeRandomLengthString();

    // Call the function-under-test with the JSON object and the consumed string
    json_object_object_add(jobj, "key", json_object_new_string(str.c_str()));

    // Decrement the reference count of the JSON object to free resources
    json_object_put(jobj);

    return 0;
}