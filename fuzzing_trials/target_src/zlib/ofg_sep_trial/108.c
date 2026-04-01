#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    z_stream strm;
    const char *version = ZLIB_VERSION;
    int stream_size = (int)sizeof(z_stream);

    // Initialize the z_stream structure
    memset(&strm, 0, sizeof(z_stream));

    // Ensure data is not NULL and has a minimum size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Allocate memory for output buffer
    size_t output_size = size * 2; // Initial guess for output size
    uint8_t *output = (uint8_t *)malloc(output_size);
    if (output == NULL) {
        return 0;
    }

    // Set up the z_stream structure for inflation
    strm.next_in = (Bytef *)data;
    strm.avail_in = size;
    strm.next_out = output;
    strm.avail_out = output_size;

    // Initialize the inflation process
    int ret = inflateInit_(&strm, version, stream_size);
    if (ret != Z_OK) {
        free(output);
        return 0;
    }

    // Perform inflation
    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateEnd(&strm);
        free(output);
        return 0;
    }

    // Cleanup
    inflateEnd(&strm);
    free(output);

    return 0;
}