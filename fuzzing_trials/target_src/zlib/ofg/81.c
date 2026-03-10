#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Initialize the crc parameter with a non-zero value
    unsigned long crc = 1;

    // Ensure size is not zero to prevent passing NULL to crc32
    if (size > 0) {
        // Call the function-under-test
        uLong result = crc32(crc, data, (uInt)size);

        // Use the result to prevent compiler optimizations from removing the call
        if (result == 0) {
            // Do nothing, just a dummy check
        }
    }

    return 0;
}

#ifdef __cplusplus
}
#endif