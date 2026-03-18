#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate stream
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure the size is sufficient for the parameters
    if (size < 4) {
        deflateEnd(&stream);
        return 0;
    }

    // Extract parameters from the input data
    int good_length = data[0];
    int max_lazy = data[1];
    int nice_length = data[2];
    int max_chain = data[3];

    // Call the function under test
    deflateTune(&stream, good_length, max_lazy, nice_length, max_chain);

    // Clean up
    deflateEnd(&stream);

    return 0;
}