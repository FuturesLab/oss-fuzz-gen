#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize the stream for deflation
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Allocate output buffer
    unsigned char outbuffer[1024];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Call the function-under-test
    ret = deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);

    return 0;
}