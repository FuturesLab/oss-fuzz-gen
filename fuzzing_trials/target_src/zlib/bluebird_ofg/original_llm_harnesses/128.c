#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the parameters
    if (size < 10) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Extract parameters from the data
    int windowBits = (int)data[0] % 16; // Valid range for windowBits is -15 to 15
    const char *version = ZLIB_VERSION;
    int stream_size = (int)data[1] % 128; // A reasonable size for the stream structure

    // Call the function-under-test
    int result = inflateInit2_(&stream, windowBits, version, stream_size);

    // Clean up
    inflateEnd(&stream);

    return 0;
}