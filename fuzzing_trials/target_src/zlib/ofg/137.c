#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize the inflate state
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Allocate a buffer for the decompressed data
    unsigned char outbuffer[32768];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Call the function-under-test
    ret = inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);

    return 0;
}