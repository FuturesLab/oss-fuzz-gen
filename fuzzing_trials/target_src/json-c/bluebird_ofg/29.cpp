#include "fuzzer/FuzzedDataProvider.h"
#include <cstddef>
#include <cstdint>

extern "C" int json_parse_double(const char *, double *);

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume a string from the input data
    std::string json_string = fuzzed_data_provider.ConsumeRemainingBytesAsString();

    // Prepare a double variable to be used as an output parameter
    double output_double = 0.0;

    // Call the function-under-test
    json_parse_double(json_string.c_str(), &output_double);

    return 0;
}