// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    int level = Z_DEFAULT_COMPRESSION;
    int method = Z_DEFLATED;
    int windowBits = 15;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    int ret = deflateInit2_(&strm, level, method, windowBits, memLevel, strategy, version, stream_size);
    if (ret != Z_OK) return 0;

    Bytef dictionary[32];
    uInt dictLength = sizeof(dictionary);
    ret = deflateGetDictionary(&strm, dictionary, &dictLength);

    if (ret == Z_OK) {
        ret = deflateSetDictionary(&strm, dictionary, dictLength);
    }

    strm.next_in = (z_const Bytef *)Data;
    strm.avail_in = Size;

    Bytef out[1024];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    ret = deflate(&strm, Z_FINISH);
    if (ret == Z_STREAM_ERROR) {
        deflateEnd(&strm);
        return 0;
    }

    ret = deflatePrime(&strm, 3, 5);
    if (ret == Z_OK || ret == Z_BUF_ERROR) {
        // Continue with deflate
        strm.next_in = (z_const Bytef *)Data;
        strm.avail_in = Size;
        ret = deflate(&strm, Z_FINISH);
    }

    ret = deflateEnd(&strm);
    return 0;
}