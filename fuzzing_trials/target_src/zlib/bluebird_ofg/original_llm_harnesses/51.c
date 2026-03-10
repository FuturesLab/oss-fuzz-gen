#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;
    unsigned char outbuffer[1024];

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Initialize the inflation process
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    ret = inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);

    return 0;
}