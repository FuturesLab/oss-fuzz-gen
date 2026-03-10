// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// inflateReset at inflate.c:125:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <zlib.h>

#define ZLIB_VERSION "1.2.11"

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    z_stream deflate_stream, inflate_stream;
    initialize_stream(&deflate_stream);
    initialize_stream(&inflate_stream);

    int level = Data[0] % 10;  // Compression level from 0 to 9

    // Initialize deflate
    if (deflateInit_(&deflate_stream, level, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // End deflate
    deflateEnd(&deflate_stream);

    // Initialize inflate
    if (inflateInit_(&inflate_stream, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // Reset deflate
    deflateReset(&deflate_stream);

    // Reset inflate
    inflateReset(&inflate_stream);

    // Reset deflate again
    deflateReset(&deflate_stream);

    // End inflate
    inflateEnd(&inflate_stream);

    // End deflate again
    deflateEnd(&deflate_stream);

    return 0;
}