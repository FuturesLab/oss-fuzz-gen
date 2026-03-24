#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <string>

// Include the header file where json_parse_uint64 is declared
#include <json-c/json_util.h>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the fuzzed data for the first parameter
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();

    // Prepare a uint64_t variable for the second parameter
    uint64_t result;

    // Check if the json_string is not empty before proceeding
    if (!json_string.empty()) {
        // Call the function-under-test
        json_parse_uint64(json_string.c_str(), &result);
    }

    return 0;
}