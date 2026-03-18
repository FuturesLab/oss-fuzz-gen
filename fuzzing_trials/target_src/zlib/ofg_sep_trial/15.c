#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    z_stream stream;
    int level, method, windowBits, memLevel, strategy;
    const char *version;
    int stream_size;
    
    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Define and initialize parameters for deflateInit2_
    level = Z_DEFAULT_COMPRESSION;  // Compression level
    method = Z_DEFLATED;            // Compression method
    windowBits = 15;                // Window size
    memLevel = 8;                   // Memory level
    strategy = Z_DEFAULT_STRATEGY;  // Compression strategy
    version = ZLIB_VERSION;         // Zlib version
    stream_size = sizeof(z_stream); // Size of the z_stream structure

    // Call the function-under-test
    if (deflateInit2_(&stream, level, method, windowBits, memLevel, strategy, version, stream_size) != Z_OK) {
        return 0;
    }

    // Allocate output buffer
    unsigned char outbuffer[4096];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Perform deflate
    while (stream.avail_in != 0) {
        deflate(&stream, Z_NO_FLUSH);
    }
    deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);

    return 0;
}