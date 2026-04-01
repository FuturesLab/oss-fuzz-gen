#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    z_stream stream;
    uLong sourceLen;

    // Initialize z_stream
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Set sourceLen to a non-zero value
    sourceLen = (uLong)size;

    // Call the function-under-test
    uLong bound = deflateBound(&stream, sourceLen);

    // Use the result to avoid compiler optimizations
    if (bound == 0) {
        return 1;
    }

    return 0;
}