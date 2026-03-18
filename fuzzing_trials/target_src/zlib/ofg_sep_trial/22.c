#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    
    // Initialize deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Initialize gz_header structure
    gz_header header;
    header.text = 1;
    header.time = 0;
    header.xflags = 0;
    header.os = 0;
    header.extra = (Bytef*)data;
    header.extra_len = size > 0 ? 1 : 0;
    header.extra_max = size > 0 ? 1 : 0;
    header.name = (Bytef*)"name";
    header.name_max = 4;
    header.comment = (Bytef*)"comment";
    header.comm_max = 7;
    header.hcrc = 0;
    header.done = 0;

    // Call the function-under-test
    deflateSetHeader(&stream, &header);

    // Clean up
    deflateEnd(&stream);

    return 0;
}