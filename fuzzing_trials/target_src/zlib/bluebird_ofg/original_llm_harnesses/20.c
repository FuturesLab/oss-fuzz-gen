#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Allocate input and output buffers
    uint8_t out[1024];
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;
    stream.avail_out = sizeof(out);
    stream.next_out = out;

    // Call the function-under-test
    int result = deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);

    return 0;
}