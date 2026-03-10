#include <stdint.h>
#include <stddef.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    z_stream stream;
    int level, method, windowBits, memLevel, strategy;
    const char *version;
    int stream_size;

    // Initialize z_stream
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Ensure the data size is sufficient to extract parameters
    if (size < 6) {
        return 0;
    }

    // Extract parameters from the input data
    level = data[0] % 10;  // Compression level (0-9)
    method = Z_DEFLATED;   // Compression method (usually Z_DEFLATED)
    windowBits = (data[1] % 16) + 8;  // windowBits (8-15)
    memLevel = (data[2] % 9) + 1;     // memLevel (1-9)
    strategy = data[3] % 5;           // Strategy (0-4)
    version = ZLIB_VERSION;           // Use the zlib version
    stream_size = sizeof(z_stream);   // Size of z_stream structure

    // Call the function under test
    int ret = deflateInit2_(&stream, level, method, windowBits, memLevel, strategy, version, stream_size);

    // Clean up
    deflateEnd(&stream);

    return 0;
}