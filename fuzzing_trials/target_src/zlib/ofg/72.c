#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to initialize two z_stream structures
    if (size < 2 * sizeof(z_stream)) {
        return 0;
    }

    // Allocate and initialize two z_stream structures
    z_stream strm1;
    z_stream strm2;

    memset(&strm1, 0, sizeof(z_stream));
    memset(&strm2, 0, sizeof(z_stream));

    // Initialize the first z_stream with some data
    strm1.next_in = (Bytef *)data;
    strm1.avail_in = size / 2;
    strm1.next_out = (Bytef *)malloc(size);
    strm1.avail_out = size;

    // Initialize the second z_stream with some data
    strm2.next_in = (Bytef *)(data + size / 2);
    strm2.avail_in = size / 2;
    strm2.next_out = (Bytef *)malloc(size);
    strm2.avail_out = size;

    // Initialize the first stream for inflation
    if (inflateInit(&strm1) != Z_OK) {
        free(strm1.next_out);
        free(strm2.next_out);
        return 0;
    }

    // Call the function-under-test
    inflateCopy(&strm2, &strm1);

    // Clean up
    inflateEnd(&strm1);
    inflateEnd(&strm2);
    free(strm1.next_out);
    free(strm2.next_out);

    return 0;
}