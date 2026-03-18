#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize the adler value
    uLong adler = 1; // Starting value for adler32

    // Call the function-under-test
    uLong result = adler32_z(adler, (const Bytef *)data, (z_size_t)size);

    // Use the result to prevent compiler optimizations from removing the call
    if (result == 0) {
        // Do nothing, just a dummy check to use the result
    }

    return 0;
}