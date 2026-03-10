// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflatePending at deflate.c:723:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflateResetKeep at deflate.c:645:13 in zlib.h
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflateCopy at deflate.c:1318:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateParams at deflate.c:775:13 in zlib.h
// deflateInit_ at deflate.c:380:13 in zlib.h
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

static void fuzz_deflateGetDictionary(z_streamp strm) {
    Bytef dictionary[32768];
    uInt dictLength;
    deflateGetDictionary(strm, dictionary, &dictLength);
}

static void fuzz_deflatePending(z_streamp strm) {
    unsigned pending;
    int bits;
    deflatePending(strm, &pending, &bits);
}

static void fuzz_deflateSetDictionary(z_streamp strm, const uint8_t *Data, size_t Size) {
    deflateSetDictionary(strm, Data, Size > 32768 ? 32768 : (uInt)Size);
}

static void fuzz_deflateResetKeep(z_streamp strm) {
    deflateResetKeep(strm);
}

static void fuzz_deflateCopy(z_streamp source) {
    z_stream dest;
    dest.zalloc = Z_NULL;
    dest.zfree = Z_NULL;
    dest.opaque = Z_NULL;
    if (deflateInit(&dest, Z_DEFAULT_COMPRESSION) == Z_OK) {
        deflateCopy(&dest, source);
        deflateEnd(&dest);
    }
}

static void fuzz_deflateParams(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    int level = Data[0] % 10;
    int strategy = Data[1] % 5;
    deflateParams(strm, level, strategy);
}

int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    if (deflateInit(&strm, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    fuzz_deflateGetDictionary(&strm);
    fuzz_deflatePending(&strm);
    fuzz_deflateSetDictionary(&strm, Data, Size);
    fuzz_deflateResetKeep(&strm);
    fuzz_deflateCopy(&strm);
    fuzz_deflateParams(&strm, Data, Size);

    deflateEnd(&strm);
    return 0;
}