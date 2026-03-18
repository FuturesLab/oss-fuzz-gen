#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Allocate output buffer
    unsigned char out[1024];
    stream.avail_out = sizeof(out);
    stream.next_out = out;

    // Initialize the deflate stream
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    while (stream.avail_in != 0) {
        int result = deflate(&stream, Z_NO_FLUSH);
        if (result != Z_OK) {
            break;
        }
    }

    // Finish the deflate process
    deflate(&stream, Z_FINISH);

    // Clean up
    deflateEnd(&stream);

    return 0;
}