#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Use deflateInit to initialize the stream
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Allocate memory for output buffer
    size_t out_size = deflateBound(&stream, size);
    uint8_t *out = (uint8_t *)malloc(out_size);
    if (out == NULL) {
        deflateEnd(&stream);
        return 0;
    }

    // Set up output buffer
    stream.avail_out = out_size;
    stream.next_out = out;

    // Call the function-under-test
    ret = deflate(&stream, Z_FINISH);

    // Clean up by calling deflateEnd
    deflateEnd(&stream);
    free(out);

    return 0;
}