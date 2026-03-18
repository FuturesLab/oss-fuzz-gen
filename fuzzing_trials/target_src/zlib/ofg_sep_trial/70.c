#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    z_stream stream;
    gz_header header;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = (Bytef *)data;

    // Initialize the inflate state
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Initialize the gz_header structure
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

    // Call the function-under-test
    ret = inflateGetHeader(&stream, &header);
    if (ret != Z_OK) {
        inflateEnd(&stream);
        return 0;
    }

    // Perform decompression
    uint8_t outbuffer[1024];
    stream.avail_out = sizeof(outbuffer);
    stream.next_out = outbuffer;

    // Attempt to inflate some data
    do {
        ret = inflate(&stream, Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            inflateEnd(&stream);
            return 0;
        }
    } while (ret != Z_STREAM_END);

    // Clean up
    inflateEnd(&stream);

    return 0;
}