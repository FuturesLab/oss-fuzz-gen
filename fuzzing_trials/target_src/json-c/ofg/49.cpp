#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" int json_parse_uint64(const char *, uint64_t *);

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the data for the char* parameter
    std::string input_string = fuzzed_data.ConsumeRandomLengthString();
    const char *input_cstr = input_string.c_str();

    // Create a uint64_t variable to pass as a pointer to the function
    uint64_t output_value = 0;

    // Call the function-under-test
    json_parse_uint64(input_cstr, &output_value);

    return 0;
}