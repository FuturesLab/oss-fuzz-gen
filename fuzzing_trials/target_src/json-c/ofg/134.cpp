#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Call the function-under-test with the consumed string
    struct json_object *json_obj = json_object_new_string(json_string.c_str());

    // Free the allocated json_object
    json_object_put(json_obj);

    return 0;
}