#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Set input data for the stream
    stream.avail_in = (uInt)size;
    stream.next_in = (Bytef *)data;

    // Allocate a buffer for the output
    unsigned char outbuffer[1024];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Perform inflation
    inflate(&stream, Z_NO_FLUSH);

    // Call the function-under-test
    int result = inflateSyncPoint(&stream);

    // Clean up
    inflateEnd(&stream);

    return 0;
}