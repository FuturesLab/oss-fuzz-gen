#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Initialize inflate state
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Allocate memory for output buffer
    unsigned char outbuffer[32768];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Call the function-under-test
    ret = inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);

    return 0;
}