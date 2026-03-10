#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;
    unsigned char out[1024];

    if (size == 0) {
        return 0;
    }

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;
    stream.avail_out = sizeof(out);
    stream.next_out = out;

    // Initialize the deflate operation
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);

    return 0;
}