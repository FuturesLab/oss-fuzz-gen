#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate stream
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure size is sufficient for two integer parameters
    if (size < 2) {
        deflateEnd(&stream);
        return 0;
    }

    // Extract two integer parameters from the input data
    int level = data[0] % 10;  // Compression level, typically between 0-9
    int strategy = data[1] % 4; // Strategy, typically between 0-3

    // Call the function-under-test
    deflateParams(&stream, level, strategy);

    // Clean up
    deflateEnd(&stream);

    return 0;
}