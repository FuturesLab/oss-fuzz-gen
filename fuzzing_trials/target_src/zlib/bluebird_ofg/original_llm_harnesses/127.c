#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Ensure the data size is sufficient for the function call
    if (size < 1) {
        return 0;
    }

    // Initialize parameters for inflateInit2_
    int windowBits = 15; // Default value for maximum window size
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    // Call the function-under-test
    int result = inflateInit2_(&stream, windowBits, version, stream_size);

    // Clean up
    inflateEnd(&stream);

    return 0;
}