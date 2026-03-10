#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the inflate operation
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Allocate a buffer for the output
    unsigned char output[1024];
    stream.next_out = output;
    stream.avail_out = sizeof(output);

    // Perform inflation (decompression)
    inflate(&stream, Z_NO_FLUSH);

    // Call the function under test
    inflateEnd(&stream);

    return 0;
}