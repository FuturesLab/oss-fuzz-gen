#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    z_stream stream;
    unsigned int pending;
    int bits;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Set up the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Call deflatePending to test it
    ret = deflatePending(&stream, &pending, &bits);

    // Clean up
    deflateEnd(&stream);

    return 0;
}