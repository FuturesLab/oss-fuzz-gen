#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size < sizeof(z_stream) * 2) {
        return 0; // Ensure there's enough data for two z_stream structures
    }

    z_stream source_stream;
    z_stream dest_stream;

    // Initialize source_stream with data
    source_stream.next_in = (Bytef *)data;
    source_stream.avail_in = size / 2;
    source_stream.zalloc = Z_NULL;
    source_stream.zfree = Z_NULL;
    source_stream.opaque = Z_NULL;

    // Initialize dest_stream with remaining data
    dest_stream.next_in = (Bytef *)(data + size / 2);
    dest_stream.avail_in = size - size / 2;
    dest_stream.zalloc = Z_NULL;
    dest_stream.zfree = Z_NULL;
    dest_stream.opaque = Z_NULL;

    // Initialize both streams for inflation
    if (inflateInit(&source_stream) != Z_OK || inflateInit(&dest_stream) != Z_OK) {
        return 0; // If initialization fails, exit
    }

    // Call the function-under-test
    inflateCopy(&dest_stream, &source_stream);

    // Clean up
    inflateEnd(&source_stream);
    inflateEnd(&dest_stream);

    return 0;
}