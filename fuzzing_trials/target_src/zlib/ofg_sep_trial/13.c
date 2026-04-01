#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    uLong adler = 1; // Initial value for the adler32 checksum
    const Bytef *buffer = data;
    z_size_t length = (z_size_t)size;

    // Call the function-under-test
    uLong checksum = adler32_z(adler, buffer, length);

    // Use the checksum in some way to prevent compiler optimizations from removing the call
    if (checksum == 0) {
        return 1;
    }

    return 0;
}