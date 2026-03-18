#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize the stream for inflation
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Allocate memory for output buffer
    size_t output_buffer_size = size * 2 + 1; // Just an arbitrary size larger than input
    uint8_t *output_buffer = (uint8_t *)malloc(output_buffer_size);
    if (output_buffer == NULL) {
        inflateEnd(&stream);
        return 0;
    }

    // Prepare the stream with input data
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;
    stream.next_out = output_buffer;
    stream.avail_out = output_buffer_size;

    // Call the function-under-test
    inflate(&stream, Z_NO_FLUSH);

    // Clean up
    inflateEnd(&stream);
    free(output_buffer);

    return 0;
}