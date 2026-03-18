#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize the stream for compression
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Allocate memory for pending and bits
    unsigned int pending = 0;
    int bits = 0;

    // Call the function-under-test
    int result = deflatePending(&stream, &pending, &bits);

    // Clean up the stream
    deflateEnd(&stream);

    return 0;
}