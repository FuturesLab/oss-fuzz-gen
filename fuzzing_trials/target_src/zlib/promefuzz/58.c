// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflatePrime at deflate.c:746:13 in zlib.h
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "zlib.h"

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void handle_deflatePrime(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    int bits = Data[0] % 16; // Limit bits to a reasonable number
    int value = Data[1];
    deflatePrime(strm, bits, value);
}

static void handle_deflateInit2_(z_streamp strm) {
    int level = Z_DEFAULT_COMPRESSION;
    int method = Z_DEFLATED;
    int windowBits = 15;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);
    deflateInit2_(strm, level, method, windowBits, memLevel, strategy, version, stream_size);
}

static void handle_deflateGetDictionary(z_streamp strm) {
    Bytef dictionary[32768];
    uInt dictLength = 0;
    deflateGetDictionary(strm, dictionary, &dictLength);
}

static void handle_deflate(z_streamp strm, const uint8_t *Data, size_t Size) {
    int flush = Z_NO_FLUSH;
    if (Size > 0) {
        flush = Data[0] % 5; // Randomly choose a flush mode
    }
    deflate(strm, flush);
}

static void handle_deflateSetDictionary(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size == 0) return;
    deflateSetDictionary(strm, Data, (uInt)Size);
}

static void handle_deflateEnd(z_streamp strm) {
    deflateEnd(strm);
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    z_stream strm;
    initialize_stream(&strm);

    if (Size < 1) return 0;

    handle_deflateInit2_(&strm);

    strm.next_in = (z_const Bytef *)Data;
    strm.avail_in = (uInt)Size;

    Bytef out[32768];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    handle_deflatePrime(&strm, Data, Size);
    handle_deflateSetDictionary(&strm, Data, Size);
    handle_deflate(&strm, Data, Size);
    handle_deflateGetDictionary(&strm);
    handle_deflateEnd(&strm);

    return 0;
}