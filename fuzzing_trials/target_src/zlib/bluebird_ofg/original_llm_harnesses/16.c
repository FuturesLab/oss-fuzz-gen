#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    // Define parameters for deflateInit2_
    int level = 1; // Compression level (1-9)
    int method = Z_DEFLATED; // Compression method
    int windowBits = 15; // Base two logarithm of the window size (9-15)
    int memLevel = 8; // Memory level (1-9)
    int strategy = Z_DEFAULT_STRATEGY; // Compression strategy
    const char *version = ZLIB_VERSION; // Zlib version
    int stream_size = (int)sizeof(z_stream); // Size of the z_stream structure

    // Call the function-under-test
    int result = deflateInit2_(&stream, level, method, windowBits, memLevel, strategy, version, stream_size);

    // Check if deflateInit2_ was successful
    if (result != Z_OK) {
        return 0;
    }

    // Set the input data for zlib
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Create a buffer for compressed data
    uint8_t outbuffer[1024];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Perform the deflation
    deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);

    return 0;
}