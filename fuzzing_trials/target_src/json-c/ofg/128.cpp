#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString(size);

    // Parse the JSON string into a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // Ensure the json_object is not NULL before proceeding
    if (json_obj != NULL) {
        // Call the function-under-test
        struct lh_table *table = json_object_get_object(json_obj);

        // Cleanup
        json_object_put(json_obj);
    }

    return 0;
}