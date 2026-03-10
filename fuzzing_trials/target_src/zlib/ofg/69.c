#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize gz_header structure
    gz_header header;
    header.text = 0;
    header.time = 0;
    header.xflags = 0;
    header.os = 0;
    header.extra = NULL;
    header.extra_len = 0;
    header.extra_max = 0;
    header.name = NULL;
    header.name_max = 0;
    header.comment = NULL;
    header.comm_max = 0;
    header.hcrc = 0;
    header.done = 0;

    // Initialize inflate state
    if (inflateInit2(&stream, 15 + 32) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    int result = inflateGetHeader(&stream, &header);

    // Clean up
    inflateEnd(&stream);

    return result;
}