#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    z_stream stream;
    int windowBits;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Ensure the size is sufficient for windowBits extraction
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract windowBits from the input data
    windowBits = *(int *)data;

    // Initialize the stream for inflation
    if (inflateInit2(&stream, windowBits) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    inflateReset2(&stream, windowBits);

    // Clean up and free resources
    inflateEnd(&stream);

    return 0;
}