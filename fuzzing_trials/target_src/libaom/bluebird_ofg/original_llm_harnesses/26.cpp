#include <cstdint>
#include <cstddef>

// Assume the function is defined in an external C library
extern "C" {
    size_t aom_uleb_size_in_bytes(uint64_t value);
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Extract a uint64_t value from the input data
    uint64_t value = 0;
    for (size_t i = 0; i < sizeof(uint64_t); ++i) {
        value |= static_cast<uint64_t>(data[i]) << (i * 8);
    }

    // Call the function-under-test
    size_t result = aom_uleb_size_in_bytes(value);

    // Use the result in some way to prevent compiler optimizations from removing the call
    volatile size_t prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}