#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Initialize the parameters for crc32_z
    unsigned long crc = 0; // Initial CRC value
    const unsigned char *buf = data; // Buffer to calculate CRC
    z_size_t len = (z_size_t)size; // Length of the buffer

    // Call the function-under-test
    uLong result = crc32_z(crc, buf, len);

    // Use the result in some way to avoid compiler optimizations
    // that might remove the call to crc32_z
    if (result == 0) {
        // Do something trivial if the result is zero
        return 1;
    }

    return 0;
}