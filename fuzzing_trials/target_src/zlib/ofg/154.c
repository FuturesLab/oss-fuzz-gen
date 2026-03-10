#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Create a buffer for the output
    unsigned char outbuffer[4096];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Call inflateSyncPoint to fuzz it
    int result = inflateSyncPoint(&stream);

    // Clean up
    inflateEnd(&stream);

    return 0;
}