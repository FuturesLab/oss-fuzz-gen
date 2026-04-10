#include <stdint.h>
#include <stddef.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to meaningfully exercise the function
    if (size == 0) {
        return 0;
    }

    // Initialize the crc value
    uint32_t crc = 0;

    // Call the function-under-test
    uint32_t result = hts_crc32(crc, (const void *)data, size);

    // Use the result in some way to prevent compiler optimizations from removing the call
    // For example, we could perform a simple operation on the result
    if (result == 0xFFFFFFFF) {
        // Arbitrary operation to use the result
        return 1;
    }

    return 0;
}