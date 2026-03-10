#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    uLong adler = 1; // Initial value for adler32 checksum
    const Bytef *buffer = (const Bytef *)data;
    uInt length = (uInt)size; // Correct type for length parameter in adler32_z

    // Call the function-under-test
    uLong result = adler32_z(adler, buffer, length);

    // Use the result to avoid compiler optimizations removing the function call
    if (result == 0) {
        // Do something trivial
    }

    return 0;
}