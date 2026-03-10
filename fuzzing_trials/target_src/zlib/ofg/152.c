#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize deflate with default compression level
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure size is sufficient for accessing data
    if (size < 2) {
        deflateEnd(&stream);
        return 0;
    }

    // Use first byte of data for level and second byte for strategy
    int level = data[0] % 10; // Valid levels are 0-9
    int strategy = data[1] % 4; // Valid strategies are 0-3

    // Call the function-under-test
    deflateParams(&stream, level, strategy);

    // Clean up
    deflateEnd(&stream);

    return 0;
}