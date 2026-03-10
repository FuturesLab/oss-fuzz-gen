#include <stdint.h>
#include <stddef.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure the size is sufficient for two integers
    if (size < 2 * sizeof(int)) {
        deflateEnd(&stream);
        return 0;
    }

    // Extract two integers from the input data
    int level = ((int *)data)[0];
    int strategy = ((int *)data)[1];

    // Call the function-under-test
    deflateParams(&stream, level, strategy);

    // Clean up the deflate process
    deflateEnd(&stream);

    return 0;
}