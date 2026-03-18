#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

// Remove the 'extern "C"' linkage specification for C++
// This code is intended to be compiled as C, not C++
int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    z_stream stream;
    unsigned long result;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the stream for inflation
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Call the function-under-test
    result = inflateCodesUsed(&stream);

    // Clean up
    inflateEnd(&stream);

    return 0;
}