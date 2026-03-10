#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the stream for inflation
    if (inflateInit(&stream) != Z_OK) {
        return 0; // Initialization failed, exit
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Call the function-under-test
    long result = inflateMark(&stream);

    // Clean up and free resources
    inflateEnd(&stream);

    return 0;
}