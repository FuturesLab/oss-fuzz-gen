#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract four integers.
    if (size < 4 * sizeof(int)) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Extract four integers from the input data
    int good_length = ((int*)data)[0];
    int max_lazy = ((int*)data)[1];
    int nice_length = ((int*)data)[2];
    int max_chain = ((int*)data)[3];

    // Call the function-under-test
    deflateTune(&stream, good_length, max_lazy, nice_length, max_chain);

    // Clean up
    deflateEnd(&stream);

    return 0;
}