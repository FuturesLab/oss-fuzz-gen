// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateReset2 at inflate.c:136:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateGetDictionary at inflate.c:1167:13 in zlib.h
// inflateInit2_ at inflate.c:173:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
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
#include "zlib.h"

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void fuzz_inflateReset2(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int windowBits = Data[0] % 16;  // Window bits in the range [0, 15]
    inflateReset2(strm, windowBits);
}

static void fuzz_inflate(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    strm->avail_in = Size;
    strm->next_in = (Bytef *)Data;
    int flush = Z_NO_FLUSH;
    inflate(strm, flush);
}

static void fuzz_inflateGetDictionary(z_streamp strm) {
    Bytef dictionary[32768];  // Maximum window size
    uInt dictLength = sizeof(dictionary);
    inflateGetDictionary(strm, dictionary, &dictLength);
}

static void fuzz_inflateInit2_(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int windowBits = Data[0] % 16;  // Window bits in the range [0, 15]
    inflateInit2_(strm, windowBits, ZLIB_VERSION, sizeof(z_stream));
}

static void fuzz_inflateSetDictionary(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    inflateSetDictionary(strm, Data, (uInt)Size);
}

static void fuzz_deflateSetDictionary(z_streamp strm, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    deflateSetDictionary(strm, Data, (uInt)Size);
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    z_stream strm;
    initialize_stream(&strm);

    fuzz_inflateInit2_(&strm, Data, Size);
    fuzz_inflateReset2(&strm, Data, Size);
    fuzz_inflate(&strm, Data, Size);
    fuzz_inflateGetDictionary(&strm);
    fuzz_inflateSetDictionary(&strm, Data, Size);
    fuzz_deflateSetDictionary(&strm, Data, Size);

    inflateEnd(&strm);
    return 0;
}