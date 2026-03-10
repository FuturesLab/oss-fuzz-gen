// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
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

static void setupStream(z_stream *strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static int initStream(z_stream *strm) {
    return deflateInit2_(strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(z_stream));
}

static void cleanupStream(z_stream *strm) {
    deflateEnd(strm);
}

int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    setupStream(&strm);

    if (initStream(&strm) != Z_OK) {
        return 0;
    }

    Bytef dictionary[32768];
    uInt dictLength = 32768;
    deflateGetDictionary(&strm, dictionary, &dictLength);

    deflateSetDictionary(&strm, Data, Size < dictLength ? Size : dictLength);

    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;
    Bytef outBuffer[32768];
    strm.next_out = outBuffer;
    strm.avail_out = sizeof(outBuffer);

    int flush = Z_NO_FLUSH;
    deflate(&strm, flush);

    int bits = (Size > 0) ? Data[0] % 8 : 0;
    int value = (Size > 1) ? Data[1] : 0;
    deflatePrime(&strm, bits, value);

    cleanupStream(&strm);
    return 0;
}