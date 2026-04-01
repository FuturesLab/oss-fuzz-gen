#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    z_stream stream;
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize the output buffer
    unsigned char outbuffer[4096];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Call the function-under-test
    int result = inflateInit_(&stream, version, stream_size);
    if (result == Z_OK) {
        inflate(&stream, Z_NO_FLUSH);
    }

    // Clean up
    inflateEnd(&stream);

    return 0;
}