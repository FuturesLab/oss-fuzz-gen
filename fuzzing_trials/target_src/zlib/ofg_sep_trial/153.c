#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the parameters
    if (size < 2) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Extract parameters for deflateParams from the input data
    int level = data[0] % 10;  // Compression level (0-9)
    int strategy = data[1] % 5; // Strategy (0-4)

    // Call the function-under-test
    deflateParams(&stream, level, strategy);

    // Clean up and free resources
    deflateEnd(&stream);

    return 0;
}