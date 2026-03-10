#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Initialize gz_header structure
    gz_header header;
    header.text = 0;
    header.time = 0;
    header.xflags = 0;
    header.os = 0;
    header.extra = Z_NULL;
    header.extra_len = 0;
    header.extra_max = 0;
    header.name = Z_NULL;
    header.name_max = 0;
    header.comment = Z_NULL;
    header.comm_max = 0;
    header.hcrc = 0;
    header.done = 0;

    // Initialize the inflate state
    if (inflateInit2(&stream, 15 + 32) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    inflateGetHeader(&stream, &header);

    // Clean up
    inflateEnd(&stream);

    return 0;
}