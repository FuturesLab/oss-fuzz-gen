#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    z_stream stream;
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

    // Set the input data
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Allocate memory for output buffer
    size_t output_size = compressBound(size);
    Bytef *output = (Bytef *)malloc(output_size);
    if (output == NULL) {
        deflateEnd(&stream);
        return 0;
    }

    // Set the output buffer
    stream.next_out = output;
    stream.avail_out = (uInt)output_size;

    // Perform deflate operation
    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        free(output);
        deflateEnd(&stream);
        return 0;
    }

    // Clean up
    free(output);
    deflateEnd(&stream);

    return 0;
}