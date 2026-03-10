#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    if (data == NULL || size == 0) {
        return 0;
    }

    z_stream stream;
    unsigned int pending;
    int bits;
    int ret;

    // Initialize z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the stream for deflate
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Set up the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Allocate memory for output buffer
    size_t outBufferSize = deflateBound(&stream, size);
    Bytef *outBuffer = (Bytef *)malloc(outBufferSize);
    if (outBuffer == NULL) {
        deflateEnd(&stream);
        return 0;
    }
    stream.next_out = outBuffer;
    stream.avail_out = (uInt)outBufferSize;

    // Perform deflation
    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        free(outBuffer);
        deflateEnd(&stream);
        return 0;
    }

    // Call the function under test
    ret = deflatePending(&stream, &pending, &bits);

    // Clean up
    free(outBuffer);
    deflateEnd(&stream);

    return 0;
}