#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstring>
#include <iostream>

extern "C" int json_parse_int64(const char *, int64_t *);

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the fuzzing data.
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string from the fuzzing data for the JSON input.
    std::string json_input = fuzzed_data.ConsumeBytesAsString(fuzzed_data.remaining_bytes());

    // Prepare the int64_t pointer for the output.
    int64_t output_value;

    // Call the function-under-test with the fuzzed inputs.
    json_parse_int64(json_input.c_str(), &output_value);

    return 0;
}