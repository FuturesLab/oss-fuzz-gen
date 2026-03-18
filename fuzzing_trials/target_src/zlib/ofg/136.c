#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>  // Include string.h for memcpy

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;  // Set input data
    stream.avail_in = size;  // Set input size

    // Initialize the inflate operation
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Allocate a buffer for decompressed data
    uint8_t outbuffer[1024];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Call the function-under-test
    ret = inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);

    return 0;
}