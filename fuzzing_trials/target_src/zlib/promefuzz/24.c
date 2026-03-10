// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateResetKeep at deflate.c:645:13 in zlib.h
// deflateSetHeader at deflate.c:715:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// deflatePending at deflate.c:723:13 in zlib.h
// deflateUsed at deflate.c:738:13 in zlib.h
// deflateCopy at deflate.c:1318:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

static void fuzz_deflateResetKeep(z_streamp strm) {
    deflateResetKeep(strm);
}

static void fuzz_deflateSetHeader(z_streamp strm) {
    gz_header header;
    memset(&header, 0, sizeof(header));
    deflateSetHeader(strm, &header);
}

static void fuzz_deflateReset(z_streamp strm) {
    deflateReset(strm);
}

static void fuzz_deflatePending(z_streamp strm) {
    unsigned pending;
    int bits;
    deflatePending(strm, &pending, &bits);
}

static void fuzz_deflateUsed(z_streamp strm) {
    int bits;
    deflateUsed(strm, &bits);
}

static void fuzz_deflateCopy(z_streamp source) {
    z_stream dest;
    initialize_stream(&dest);
    deflateCopy(&dest, source);
    cleanup_stream(&dest);
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;

    Bytef out_buffer[4096];
    strm.next_out = out_buffer;
    strm.avail_out = sizeof(out_buffer);

    // Fuzz each function
    fuzz_deflateResetKeep(&strm);
    fuzz_deflateSetHeader(&strm);
    fuzz_deflateReset(&strm);
    fuzz_deflatePending(&strm);
    fuzz_deflateUsed(&strm);
    fuzz_deflateCopy(&strm);

    cleanup_stream(&strm);
    return 0;
}