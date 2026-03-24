#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <string>

// Include the correct headers for json-c
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Parse the JSON string into a json_object
    struct json_object *json_obj = json_tokener_parse(json_string.c_str());

    // If parsing was successful, call json_object_put
    if (json_obj != nullptr) {
        json_object_put(json_obj);
    }

    return 0;
}