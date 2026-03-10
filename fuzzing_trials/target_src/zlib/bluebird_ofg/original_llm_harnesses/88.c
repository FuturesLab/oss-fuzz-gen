#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize the adler value to a non-zero value
    uLong adler = 1;

    // Ensure size is within the range of uInt
    uInt length = (uInt)size;

    // Call the function-under-test
    uLong result = adler32(adler, (const Bytef *)data, length);

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}