#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Allocate some memory for input and output buffers
    unsigned char out_buffer[256];
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;
    stream.next_out = out_buffer;
    stream.avail_out = sizeof(out_buffer);

    // Initialize the inflation process
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    int result = inflateSync(&stream);

    // Clean up
    inflateEnd(&stream);

    return 0;
}