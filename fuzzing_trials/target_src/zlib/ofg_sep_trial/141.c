#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    // Allocate memory for input and output buffers
    uInt input_size = size > 0 ? size : 1; // Ensure non-zero size
    uInt output_size = compressBound(input_size);
    Bytef *input_buffer = (Bytef *)malloc(input_size);
    Bytef *output_buffer = (Bytef *)malloc(output_size);

    if (input_buffer == NULL || output_buffer == NULL) {
        free(input_buffer);
        free(output_buffer);
        return 0;
    }

    // Copy the input data into the input buffer
    memcpy(input_buffer, data, input_size);

    // Initialize the z_stream
    stream.next_in = input_buffer;
    stream.avail_in = input_size;
    stream.next_out = output_buffer;
    stream.avail_out = output_size;

    // Initialize the deflate operation
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        free(input_buffer);
        free(output_buffer);
        return 0;
    }

    // Call the function-under-test
    deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);
    free(input_buffer);
    free(output_buffer);

    return 0;
}