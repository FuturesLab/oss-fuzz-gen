#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize gz_header structure
    gz_header header;
    header.text = 0;
    header.time = 0;
    header.xflags = 0;
    header.os = 0;
    header.extra = (Bytef *)data;
    header.extra_len = size;
    header.extra_max = size;
    header.name = (Bytef *)data;
    header.name_max = size;
    header.comment = (Bytef *)data;
    header.comm_max = size;
    header.hcrc = 0;
    header.done = 0;

    // Initialize the stream for compression
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Call deflateSetHeader with the initialized structures
    deflateSetHeader(&stream, &header);

    // Clean up
    deflateEnd(&stream);

    return 0;
}