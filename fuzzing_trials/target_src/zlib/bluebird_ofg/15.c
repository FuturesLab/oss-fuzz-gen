#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    
    // Ensure the input size is non-zero
    uLong inputSize = size > 0 ? size : 1;

    // Initialize the stream for compression
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0; // Initialization failed, return early
    }

    // Call the function-under-test
    uLong bound = deflateBound(&stream, inputSize);

    // Use the result in some way to avoid compiler optimizations
    if (bound > 0) {
        // Do something with the bound, e.g., print or log
    }

    // Clean up
    deflateEnd(&stream);

    return 0;
}