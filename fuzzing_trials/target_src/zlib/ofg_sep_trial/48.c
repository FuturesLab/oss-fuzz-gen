#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure that we have enough data to extract four integers
    if (size < 16) {
        deflateEnd(&stream);
        return 0;
    }

    // Extract four integers from the input data
    int good_length = (int)data[0] | ((int)data[1] << 8) | ((int)data[2] << 16) | ((int)data[3] << 24);
    int max_lazy = (int)data[4] | ((int)data[5] << 8) | ((int)data[6] << 16) | ((int)data[7] << 24);
    int nice_length = (int)data[8] | ((int)data[9] << 8) | ((int)data[10] << 16) | ((int)data[11] << 24);
    int max_chain = (int)data[12] | ((int)data[13] << 8) | ((int)data[14] << 16) | ((int)data[15] << 24);

    // Call the function-under-test
    deflateTune(&stream, good_length, max_lazy, nice_length, max_chain);

    // Clean up
    deflateEnd(&stream);

    return 0;
}