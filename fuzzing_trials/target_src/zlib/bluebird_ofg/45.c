#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Set input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Allocate a buffer for output
    size_t output_buffer_size = size * 2; // Just an arbitrary size for output buffer
    Bytef *output_buffer = (Bytef *)malloc(output_buffer_size);
    if (output_buffer == NULL) {
        inflateEnd(&stream);
        return 0;
    }
    stream.next_out = output_buffer;
    stream.avail_out = output_buffer_size;

    // Perform inflation to fill the output buffer
    int ret = inflate(&stream, Z_NO_FLUSH);

    // Call the function-under-test
    int sync_point = inflateSyncPoint(&stream);

    // Clean up
    inflateEnd(&stream);
    free(output_buffer);

    return 0;
}

#ifdef __cplusplus
}
#endif