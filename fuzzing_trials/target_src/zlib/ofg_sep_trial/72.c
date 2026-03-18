#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    z_stream source_stream;
    z_stream dest_stream;
    int ret;

    // Initialize source stream
    source_stream.zalloc = Z_NULL;
    source_stream.zfree = Z_NULL;
    source_stream.opaque = Z_NULL;
    source_stream.avail_in = size;
    source_stream.next_in = (Bytef *)data;
    ret = inflateInit(&source_stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Initialize destination stream
    dest_stream.zalloc = Z_NULL;
    dest_stream.zfree = Z_NULL;
    dest_stream.opaque = Z_NULL;
    dest_stream.avail_out = size;
    dest_stream.next_out = (Bytef *)malloc(size);
    if (dest_stream.next_out == NULL) {
        inflateEnd(&source_stream);
        return 0;
    }
    ret = inflateInit(&dest_stream);
    if (ret != Z_OK) {
        free(dest_stream.next_out);
        inflateEnd(&source_stream);
        return 0;
    }

    // Call the function-under-test
    inflateCopy(&dest_stream, &source_stream);

    // Clean up
    free(dest_stream.next_out);
    inflateEnd(&source_stream);
    inflateEnd(&dest_stream);

    return 0;
}