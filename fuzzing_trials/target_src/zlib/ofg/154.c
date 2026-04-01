#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;
    unsigned char outbuffer[32768]; // Buffer to hold decompressed data
    int have;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Initialize the inflation process
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Inflate until output buffer is not full
    do {
        stream.avail_out = sizeof(outbuffer);
        stream.next_out = outbuffer;

        ret = inflate(&stream, Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR) {
            // Stream error, break out
            break;
        }

        switch (ret) {
        case Z_NEED_DICT:
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            inflateEnd(&stream);
            return 0;
        }

        have = sizeof(outbuffer) - stream.avail_out;

    } while (stream.avail_out == 0);

    // Clean up
    inflateEnd(&stream);

    return 0;
}