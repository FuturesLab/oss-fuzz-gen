#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    z_stream stream;
    gz_header header;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Initialize the deflate stream
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Initialize the gz_header structure
    header.text = 0;
    header.time = 0;
    header.xflags = 0;
    header.os = 0;
    header.extra = (Bytef *)data;
    header.extra_len = size;
    header.extra_max = size;
    header.name = (Bytef *)"test";
    header.comment = (Bytef *)"fuzzing";
    header.hcrc = 0;
    header.done = 0;

    // Call the function under test
    ret = deflateSetHeader(&stream, &header);

    // Clean up
    deflateEnd(&stream);

    return 0;
}