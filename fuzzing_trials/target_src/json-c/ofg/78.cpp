#include <fuzzer/FuzzedDataProvider.h>

extern "C" int json_global_set_string_hash(const int);

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume an integer value from the fuzzed data
    int input_value = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_global_set_string_hash(input_value);

    return 0;
}