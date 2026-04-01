#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string str = fuzzed_data.ConsumeRandomLengthString();

    // Consume an integer from the fuzzed data for the length parameter
    int len = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    struct json_object *json_obj = json_object_new_string_len(str.c_str(), len);

    // Clean up the created json_object if it's not NULL
    if (json_obj != NULL) {
        json_object_put(json_obj);
    }

    return 0;
}