#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

extern int inflateUndermine(z_streamp strm, int subvert);

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Declare and initialize variables
    z_stream stream;
    int subvert = 1; // A non-zero value for subvert

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = (uInt)size;
    stream.next_in = (Bytef *)data;

    // Allocate output buffer
    unsigned char outbuffer[4096];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    int result = inflateUndermine(&stream, subvert);

    // Check the result to ensure the function is being invoked
    if (result != Z_OK && result != Z_STREAM_END) {
        inflateEnd(&stream);
        return 0;
    }

    // Clean up
    inflateEnd(&stream);

    return 0;
}