#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"  // Include the header for json_tokener_parse

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the given data and size
    FuzzedDataProvider fuzzed_data(data, size);

    // Use the fuzzed data to create a string
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the string into a JSON object
    struct json_object *obj = json_tokener_parse(json_string.c_str());

    // Clean up
    if (obj != NULL) {
        json_object_put(obj);
    }

    return 0;
}