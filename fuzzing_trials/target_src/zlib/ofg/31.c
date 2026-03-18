#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize the crc variable with a non-zero value
    unsigned long crc = 1;

    // Call the function-under-test
    uLong result = crc32_z(crc, data, (z_size_t)size);

    // Use the result in some way to avoid compiler optimizations
    // that might remove the call to crc32_z
    if (result == 0) {
        return 0;
    }

    return 0;
}