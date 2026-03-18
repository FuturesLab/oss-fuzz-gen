// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflatePending at deflate.c:723:13 in zlib.h
// deflateUsed at deflate.c:738:13 in zlib.h
// deflateCopy at deflate.c:1318:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// deflateResetKeep at deflate.c:645:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void initialize_z_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(int)) {
        return 0;
    }

    z_stream strm;
    initialize_z_stream(&strm);

    int level = Data[0] % 10; // compression level from 0 to 9
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    int ret = deflateInit_(&strm, level, version, stream_size);
    if (ret != Z_OK) {
        return 0;
    }

    unsigned pending;
    int bits;
    deflatePending(&strm, &pending, &bits);
    deflateUsed(&strm, &bits);

    z_stream dest;
    initialize_z_stream(&dest);
    deflateCopy(&dest, &strm);

    deflateReset(&strm);
    deflateResetKeep(&strm);

    deflateEnd(&strm);
    deflateEnd(&dest);

    return 0;
}