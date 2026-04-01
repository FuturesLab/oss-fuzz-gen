#include <cstdint>
#include <cstddef>

// Assuming the function is defined in an external C library
extern "C" {
    size_t aom_uleb_size_in_bytes(uint64_t value);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure that the input size is at least the size of a uint64_t
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Interpret the first 8 bytes of data as a uint64_t
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