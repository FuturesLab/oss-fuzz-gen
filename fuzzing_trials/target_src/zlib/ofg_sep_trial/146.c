#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    memset(&stream, 0, sizeof(stream));
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Allocate memory for output buffer
    size_t output_size = size * 2 + 1; // Just to ensure we have enough space
    Bytef *output = (Bytef *)malloc(output_size);
    if (output == NULL) {
        return 0; // Memory allocation failed
    }
    stream.next_out = output;
    stream.avail_out = (uInt)output_size;

    // Initialize inflate
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        free(output);
        return 0;
    }

    // Call the function-under-test
    ret = inflateSync(&stream);

    // Clean up
    inflateEnd(&stream);
    free(output);

    return 0;
}