// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateReset at inflate.c:125:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

static int initialize_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->avail_in = 0;
    strm->next_in = Z_NULL;
    strm->avail_out = 0;
    strm->next_out = Z_NULL;
    return 0;
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    // deflateInit_
    if (deflateInit_(&strm, Z_DEFAULT_COMPRESSION, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // deflateEnd
    if (deflateEnd(&strm) != Z_OK) {
        return 0;
    }

    initialize_stream(&strm);

    // inflateInit_
    if (inflateInit_(&strm, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // deflateReset
    if (deflateReset(&strm) != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    // inflateReset
    if (inflateReset(&strm) != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    // deflateReset
    if (deflateReset(&strm) != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    // inflateEnd
    if (inflateEnd(&strm) != Z_OK) {
        return 0;
    }

    // deflateEnd
    if (deflateEnd(&strm) != Z_OK) {
        return 0;
    }

    return 0;
}