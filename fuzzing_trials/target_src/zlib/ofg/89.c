#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Initialize a non-zero adler value
    uLong adler = 1;

    // Call the function-under-test
    uLong result = adler32(adler, data, (uInt)size);

    // Use the result to avoid any compiler optimizations removing the call
    // This is a no-op, just to use the result
    if (result == 0) {
        return 1;
    }

    return 0;
}