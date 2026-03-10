#include <stdint.h>
#include <stddef.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;
    unsigned char outbuffer[1024]; // Buffer for decompressed data
    int have;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize the stream for inflation
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Decompress the data until the output buffer is not full
    do {
        stream.avail_out = sizeof(outbuffer);
        stream.next_out = outbuffer;
        
        ret = inflate(&stream, Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR) {
            // Stream state was inconsistent
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
        // Optionally process the decompressed data in outbuffer
    } while (stream.avail_out == 0);

    // Clean up
    inflateEnd(&stream);

    return 0;
}