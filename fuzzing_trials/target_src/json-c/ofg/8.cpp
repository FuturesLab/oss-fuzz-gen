#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume a random length string from the fuzzed data
    std::string str = fuzzed_data_provider.ConsumeRandomLengthString(size);

    // Consume an integer for the length parameter
    int len = fuzzed_data_provider.ConsumeIntegralInRange<int>(0, str.size());

    // Call the function-under-test
    struct json_object *json_obj = json_object_new_string_len(str.c_str(), len);

    // Free the created json object
    if (json_obj != nullptr) {
        json_object_put(json_obj);
    }

    return 0;
}