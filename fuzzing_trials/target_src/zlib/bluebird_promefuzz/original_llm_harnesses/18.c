// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:173:13 in zlib.h
// inflateReset at inflate.c:125:13 in zlib.h
// inflateReset2 at inflate.c:136:13 in zlib.h
// inflateResetKeep at inflate.c:100:13 in zlib.h
// deflateResetKeep at deflate.c:645:13 in zlib.h
// inflateGetHeader at inflate.c:1219:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

static void initialize_z_stream(z_stream *strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_z_stream(&strm);

    int windowBits = Data[0] % 16 + 8; // Valid range for windowBits in zlib is 8 to 15
    int ret = inflateInit2_(&strm, windowBits, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    // Attempt to reset the stream in various ways
    inflateReset(&strm);
    inflateReset2(&strm, windowBits);
    inflateResetKeep(&strm);

    // Test deflateResetKeep
    deflateResetKeep(&strm);

    // Test inflateGetHeader
    gz_header header;
    memset(&header, 0, sizeof(gz_header));
    inflateGetHeader(&strm, &header);

    inflateEnd(&strm);

    return 0;
}