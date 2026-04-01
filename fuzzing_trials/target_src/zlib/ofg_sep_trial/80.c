#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Initialize the z_stream structures
    z_stream source_stream;
    z_stream dest_stream;

    // Ensure the data size is sufficient for initialization
    if (size < sizeof(z_stream) * 2) {
        return 0;
    }

    // Initialize the source stream
    source_stream.next_in = (Bytef *)data;
    source_stream.avail_in = (uInt)size;
    source_stream.zalloc = Z_NULL;
    source_stream.zfree = Z_NULL;
    source_stream.opaque = Z_NULL;

    // Initialize the destination stream
    dest_stream.next_in = Z_NULL;
    dest_stream.avail_in = 0;
    dest_stream.zalloc = Z_NULL;
    dest_stream.zfree = Z_NULL;
    dest_stream.opaque = Z_NULL;

    // Initialize the source stream for deflate
    if (deflateInit(&source_stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    deflateCopy(&dest_stream, &source_stream);

    // Clean up
    deflateEnd(&source_stream);
    deflateEnd(&dest_stream);

    return 0;
}