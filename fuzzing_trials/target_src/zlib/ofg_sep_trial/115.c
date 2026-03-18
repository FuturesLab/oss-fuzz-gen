#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    z_stream stream;
    
    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    
    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;
    
    // Allocate output buffer
    size_t outputBufferSize = size + 256; // Slightly larger than input
    Bytef *outputBuffer = (Bytef *)malloc(outputBufferSize);
    if (outputBuffer == NULL) {
        deflateEnd(&stream);
        return 0;
    }
    
    // Set the output buffer for the stream
    stream.next_out = outputBuffer;
    stream.avail_out = (uInt)outputBufferSize;
    
    // Perform deflate operation
    deflate(&stream, Z_FINISH);
    
    // Clean up
    deflateEnd(&stream);
    free(outputBuffer);
    
    return 0;
}