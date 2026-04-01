#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Initialize a z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Initialize the inflate operation
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Allocate a buffer for the decompressed output
    unsigned char outbuffer[32768];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Inflate the data
    while (stream.avail_in != 0) {
        int result = inflate(&stream, Z_NO_FLUSH);
        if (result == Z_STREAM_END) {
            break;
        }
        if (result != Z_OK) {
            inflateEnd(&stream);
            return 0;
        }
    }

    // Clean up
    inflateEnd(&stream);

    return 0;
}