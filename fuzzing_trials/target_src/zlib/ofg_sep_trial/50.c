#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
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

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Allocate a buffer for the output
    unsigned char outbuffer[4096];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Call the function-under-test
    int ret = inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);

    return 0;
}