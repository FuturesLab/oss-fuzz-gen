#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    // Allocate memory for input and output buffers
    unsigned char *in = (unsigned char *)malloc(size);
    unsigned char *out = (unsigned char *)malloc(size * 2); // Output buffer can be larger

    if (in == NULL || out == NULL) {
        free(in);
        free(out);
        return 0;
    }

    // Copy data to input buffer
    memcpy(in, data, size);

    // Initialize the z_stream structure for deflation
    stream.next_in = in;
    stream.avail_in = size;
    stream.next_out = out;
    stream.avail_out = size * 2;

    // Initialize deflate with default compression level
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        free(in);
        free(out);
        return 0;
    }

    // Call the function-under-test
    deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);
    free(in);
    free(out);

    return 0;
}