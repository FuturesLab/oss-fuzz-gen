// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateParams at deflate.c:775:13 in zlib.h
// deflatePending at deflate.c:723:13 in zlib.h
// deflateUsed at deflate.c:738:13 in zlib.h
// deflateTune at deflate.c:820:13 in zlib.h
// deflateCopy at deflate.c:1318:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void try_deflateParams(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    int level = Data[0] % 10; // valid level range is 0-9
    int strategy = Data[1] % 5; // valid strategy range is 0-4
    deflateParams(strm, level, strategy);
}

static void try_deflatePending(z_streamp strm) {
    unsigned pending;
    int bits;
    deflatePending(strm, &pending, &bits);
}

static void try_deflateUsed(z_streamp strm) {
    int bits;
    deflateUsed(strm, &bits);
}

static void try_deflateTune(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    int good_length = Data[0] % 258; // arbitrary max value
    int max_lazy = Data[1] % 258; // arbitrary max value
    int nice_length = Data[2] % 258; // arbitrary max value
    int max_chain = Data[3] % 4096; // arbitrary max value
    deflateTune(strm, good_length, max_lazy, nice_length, max_chain);
}

static void try_deflateCopy(z_streamp source) {
    z_stream dest;
    initialize_stream(&dest);
    deflateCopy(&dest, source);
    deflateEnd(&dest);
}

static void try_deflateInit(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int level = Data[0] % 10; // valid level range is 0-9
    deflateInit_(strm, level, ZLIB_VERSION, sizeof(z_stream));
}

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    z_stream strm;
    initialize_stream(&strm);

    try_deflateInit(&strm, Data, Size);
    try_deflateParams(&strm, Data, Size);
    try_deflatePending(&strm);
    try_deflateUsed(&strm);
    try_deflateTune(&strm, Data, Size);
    try_deflateCopy(&strm);

    deflateEnd(&strm);
    return 0;
}