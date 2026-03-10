#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Declare and initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate operation
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Set up the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Allocate a buffer for the output
    size_t outputBufferSize = size + 256; // Extra space for potential expansion
    Bytef *outputBuffer = (Bytef *)malloc(outputBufferSize);
    if (outputBuffer == NULL) {
        deflateEnd(&stream);
        return 0;
    }

    // Set up the output buffer for the stream
    stream.next_out = outputBuffer;
    stream.avail_out = outputBufferSize;

    // Perform the deflate operation
    deflate(&stream, Z_FINISH);

    // Call the function-under-test: deflateEnd
    deflateEnd(&stream);

    // Free the allocated output buffer
    free(outputBuffer);

    return 0;
}