#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    z_stream strm;
    int ret;
    unsigned char out[4096];

    // Initialize the z_stream structure
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = (uInt)size;
    strm.next_in = (Bytef *)data;
    strm.avail_out = sizeof(out);
    strm.next_out = out;

    // Initialize the inflate process
    ret = inflateInit(&strm);
    if (ret != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    inflate(&strm, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&strm);

    return 0;
}