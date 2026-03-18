// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateResetKeep at deflate.c:645:13 in zlib.h
// deflateSetHeader at deflate.c:715:13 in zlib.h
// deflateParams at deflate.c:775:13 in zlib.h
// deflatePending at deflate.c:723:13 in zlib.h
// deflateUsed at deflate.c:738:13 in zlib.h
// deflateCopy at deflate.c:1318:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static void initialize_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    deflateInit(strm, Z_DEFAULT_COMPRESSION);
}

static void cleanup_stream(z_streamp strm) {
    deflateEnd(strm);
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    // Allocate memory for input and output
    strm.next_in = (z_const Bytef *)Data;
    strm.avail_in = Size;
    strm.next_out = (Bytef *)malloc(Size);
    strm.avail_out = Size;

    // Fuzz deflateResetKeep
    deflateResetKeep(&strm);

    // Fuzz deflateSetHeader
    gz_header header;
    header.text = 1;
    header.time = 0;
    header.xflags = 0;
    header.os = 0;
    header.extra = Z_NULL;
    header.extra_len = 0;
    header.name = Z_NULL;
    header.comment = Z_NULL;
    header.hcrc = 0;
    header.done = 0;
    deflateSetHeader(&strm, &header);

    // Fuzz deflateParams
    int level = Data[0] % 10; // valid levels are 0-9
    int strategy = Data[0] % 5; // valid strategies are 0-4
    deflateParams(&strm, level, strategy);

    // Fuzz deflatePending
    unsigned pending;
    int bits;
    deflatePending(&strm, &pending, &bits);

    // Fuzz deflateUsed
    deflateUsed(&strm, &bits);

    // Fuzz deflateCopy
    z_stream dest;
    initialize_stream(&dest);
    deflateCopy(&dest, &strm);
    cleanup_stream(&dest);

    // Cleanup
    free((void *)strm.next_out);
    cleanup_stream(&strm);

    return 0;
}