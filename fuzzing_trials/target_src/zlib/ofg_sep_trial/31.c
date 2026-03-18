#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    unsigned long crc = 0; // Initial CRC value
    const unsigned char *buffer = data; // Buffer to calculate CRC on
    z_size_t length = (z_size_t)size; // Length of the buffer

    // Call the function-under-test
    uLong result = crc32_z(crc, buffer, length);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result == 0) {
        // Do something if needed, or just return
        return 0;
    }

    return 0;
}