#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the stream for deflate operation
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure the input data is not NULL
    if (size > 0) {
        stream.next_in = (Bytef *)data;
        stream.avail_in = (uInt)size;
    } else {
        // If size is 0, return early as there's nothing to process
        deflateEnd(&stream);
        return 0;
    }

    // Set a dummy output buffer
    unsigned char outbuffer[1024];
    stream.next_out = outbuffer;
    stream.avail_out = sizeof(outbuffer);

    // Call the function-under-test
    int result;
    do {
        result = deflate(&stream, Z_FINISH);
    } while (result == Z_OK);

    // Clean up
    deflateEnd(&stream);

    return (result == Z_STREAM_END) ? 0 : 1;
}