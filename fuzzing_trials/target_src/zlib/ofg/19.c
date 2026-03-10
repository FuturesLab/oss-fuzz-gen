#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (unsigned char *)data;

    // Initialize the deflate operation
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    ret = deflateReset(&stream);

    // Clean up
    deflateEnd(&stream);

    return 0;
}