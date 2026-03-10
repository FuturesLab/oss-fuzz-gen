#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function call
    z_stream stream;
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Allocate an output buffer
    uInt output_buffer_size = 1024; // Arbitrary size for the output buffer
    Bytef *output_buffer = (Bytef *)malloc(output_buffer_size);
    if (output_buffer == NULL) {
        return 0; // If allocation fails, exit the function
    }
    stream.next_out = output_buffer;
    stream.avail_out = output_buffer_size;

    // Call the function-under-test
    int init_result = inflateInit_(&stream, version, stream_size);
    if (init_result == Z_OK) {
        // Inflate the input data
        inflate(&stream, Z_NO_FLUSH);
    }

    // Cleanup
    inflateEnd(&stream);
    free(output_buffer);

    return 0;
}