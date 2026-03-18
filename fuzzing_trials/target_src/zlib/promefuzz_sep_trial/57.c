// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateCodesUsed at inflate.c:1408:23 in zlib.h
// inflateUndermine at inflate.c:1370:13 in zlib.h
// inflatePrime at inflate.c:219:13 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void cleanup_stream(z_streamp strm) {
    inflateEnd(strm);
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    inflateInit(&strm);

    // Prepare input data
    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;

    unsigned char out[1024];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    // Fuzz inflate
    int flush = Data[0] % 6; // Random flush value
    inflate(&strm, flush);

    // Fuzz inflateCodesUsed
    inflateCodesUsed(&strm);

    // Fuzz inflateUndermine
    int subvert = Data[0] % 2;
    inflateUndermine(&strm, subvert);

    // Fuzz inflatePrime
    int bits = Data[0] % 16;
    int value = Data[0] % 256;
    inflatePrime(&strm, bits, value);

    // Fuzz inflateSync
    inflateSync(&strm);

    // Fuzz inflateCopy
    z_stream dest;
    initialize_stream(&dest);
    inflateInit(&dest);
    inflateCopy(&dest, &strm);
    cleanup_stream(&dest);

    cleanup_stream(&strm);

    return 0;
}