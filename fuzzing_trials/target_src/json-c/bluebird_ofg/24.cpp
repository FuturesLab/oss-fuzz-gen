#include "fuzzer/FuzzedDataProvider.h"

extern "C" int json_global_set_string_hash(const int);

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the fuzzing input data
    FuzzedDataProvider fuzzed_data_provider(data, size);

    // Consume an integer from the fuzzing input data
    int input_value = fuzzed_data_provider.ConsumeIntegral<int>();

    // Call the function-under-test with the consumed integer
    json_global_set_string_hash(input_value);

    return 0;
}