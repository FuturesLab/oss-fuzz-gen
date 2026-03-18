#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize deflate with default compression level
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Set input data for the z_stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Prepare an output buffer
    uint8_t out_buffer[1024];
    stream.next_out = out_buffer;
    stream.avail_out = sizeof(out_buffer);

    // Perform deflate operation
    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        deflateEnd(&stream);
        return 0;
    }

    // End deflation and clean up
    deflateEnd(&stream);

    return 0;
}