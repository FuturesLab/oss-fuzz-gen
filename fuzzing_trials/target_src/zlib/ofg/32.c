#include <stdint.h>
#include <stddef.h>
#include <zlib.h>  // Include the zlib header for crc32_z

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    uLong crc = 0;  // Initialize the crc value
    const Bytef *buffer = (const Bytef *)data;  // Cast data to the expected type
    uInt bufferSize = (uInt)size;  // Cast size to the expected type

    // Call the function-under-test
    uLong result = crc32_z(crc, buffer, bufferSize);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}