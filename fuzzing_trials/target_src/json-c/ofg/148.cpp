#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>

extern "C" {
    int json_c_set_serialization_double_format(const char *, int);
}

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a random length string from the input data
    std::string format_string = fuzzed_data.ConsumeRandomLengthString();

    // Consume an integer from the input data
    int int_value = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_c_set_serialization_double_format(format_string.c_str(), int_value);

    return 0;
}