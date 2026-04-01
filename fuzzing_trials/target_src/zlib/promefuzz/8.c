// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateParams at deflate.c:775:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateParams at deflate.c:775:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define CHUNK 256

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    uint8_t out[CHUNK];
    int ret;

    // Initialize the deflate stream
    ret = deflateInit_(&strm, Z_DEFAULT_COMPRESSION, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    // Prepare input data
    strm.next_in = Data;
    strm.avail_in = Size;

    // Prepare output buffer
    strm.next_out = out;
    strm.avail_out = CHUNK;

    // First deflate call
    ret = deflate(&strm, Z_NO_FLUSH);
    if (ret != Z_OK && ret != Z_BUF_ERROR) goto cleanup;

    // Change deflate parameters
    int level = Data[0] % 10; // Compression level 0-9
    int strategy = Data[1] % 4; // Strategy 0-3

    ret = deflateParams(&strm, level, strategy);
    if (ret != Z_OK) goto cleanup;

    // Second deflate call
    ret = deflate(&strm, Z_SYNC_FLUSH);
    if (ret != Z_OK && ret != Z_BUF_ERROR) goto cleanup;

    // Change deflate parameters again
    level = Data[2] % 10; // Compression level 0-9
    strategy = Data[2] % 4; // Strategy 0-3

    ret = deflateParams(&strm, level, strategy);
    if (ret != Z_OK) goto cleanup;

    // Third deflate call
    ret = deflate(&strm, Z_PARTIAL_FLUSH);
    if (ret != Z_OK && ret != Z_BUF_ERROR) goto cleanup;

    // Fourth deflate call
    ret = deflate(&strm, Z_FINISH);
    if (ret != Z_STREAM_END && ret != Z_BUF_ERROR) goto cleanup;

cleanup:
    // Clean up and release resources
    deflateEnd(&strm);
    return 0;
}