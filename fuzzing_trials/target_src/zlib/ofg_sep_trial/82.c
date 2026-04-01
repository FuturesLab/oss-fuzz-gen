#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Initialize the crc parameter with a non-zero value
    unsigned long crc = 1;

    // Ensure that the data is not NULL and size is not zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    uLong result = crc32(crc, data, (uInt)size);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result == 0) {
        return 0;
    }

    return 0;
}