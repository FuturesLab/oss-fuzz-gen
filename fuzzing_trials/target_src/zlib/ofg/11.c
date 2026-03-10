#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    z_stream stream;
    unsigned char out[1024]; // Output buffer
    unsigned int pending;
    int bits;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate state
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Set the output buffer for the stream
    stream.next_out = out;
    stream.avail_out = sizeof(out);

    // Perform a deflate operation
    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        deflateEnd(&stream);
        return 0;
    }

    // Call the function-under-test
    deflatePending(&stream, &pending, &bits);

    // Clean up the deflate state
    deflateEnd(&stream);

    return 0;
}