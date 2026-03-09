#include <cstdint>
#include <cstddef>
#include <aom/aom_integer.h>

extern "C" {
    size_t aom_uleb_size_in_bytes(uint64_t value);
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    if (size < sizeof(uint64_t)) {
        return 0; // Ensure there's enough data to form a uint64_t
    }

    // Interpret the first 8 bytes of data as a uint64_t
    uint64_t input_value = 0;
    for (size_t i = 0; i < sizeof(uint64_t); ++i) {
        input_value |= static_cast<uint64_t>(data[i]) << (i * 8);
    }

    // Call the function-under-test
    size_t result = aom_uleb_size_in_bytes(input_value);

    // Use the result in some way to prevent optimization out
    volatile size_t prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}