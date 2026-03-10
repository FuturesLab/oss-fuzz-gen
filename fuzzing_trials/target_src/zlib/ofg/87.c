#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    uLong adler = 1; // Starting value for adler32 checksum
    const Bytef *buffer = data;
    uInt length = (uInt)size;

    // Call the function-under-test
    uLong checksum = adler32(adler, buffer, length);

    // Use the checksum in some way to avoid compiler optimizations removing the call
    if (checksum == 0) {
        // Do something, e.g., print or log if needed
    }

    return 0;
}