#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate state
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Allocate and initialize gz_header structure
    gz_header header;
    header.text = 1; // Set some non-zero value
    header.time = 123456789;
    header.xflags = 0;
    header.os = 255;
    header.extra = (Bytef *)data;
    header.extra_len = size;
    header.extra_max = size;
    header.name = (Bytef *)"example";
    header.name_max = 7;
    header.comment = (Bytef *)"comment";
    header.comm_max = 7;
    header.hcrc = 0;
    header.done = 0;

    // Call the function-under-test
    deflateSetHeader(&stream, &header);

    // Clean up
    deflateEnd(&stream);

    return 0;
}