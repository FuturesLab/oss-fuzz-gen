#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Initialize the inflate state
    int ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Allocate a buffer for decompression output
    size_t output_buffer_size = size * 2 + 1; // Arbitrary size for testing
    Bytef *output_buffer = (Bytef *)malloc(output_buffer_size);
    if (output_buffer == NULL) {
        inflateEnd(&stream);
        return 0;
    }

    // Set the output buffer
    stream.next_out = output_buffer;
    stream.avail_out = (uInt)output_buffer_size;

    // Perform inflate operation
    inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);
    free(output_buffer);

    return 0;
}