// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateMark at inflate.c:1397:14 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
// inflateCodesUsed at inflate.c:1408:23 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
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

static void initializeStream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    inflateInit(strm);
}

static void cleanupStream(z_streamp strm) {
    inflateEnd(strm);
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initializeStream(&strm);

    // Prepare input and output buffers
    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;

    Bytef out[1024];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    // Fuzz inflate
    inflate(&strm, Z_NO_FLUSH);
    inflate(&strm, Z_FINISH);

    // Fuzz inflateMark
    long mark = inflateMark(&strm);

    // Fuzz inflateCopy
    z_stream dest;
    initializeStream(&dest);
    inflateCopy(&dest, &strm);
    cleanupStream(&dest);

    // Fuzz inflateCodesUsed
    unsigned long codesUsed = inflateCodesUsed(&strm);

    // Fuzz inflateSync
    inflateSync(&strm);

    // Fuzz inflateSetDictionary
    if (Size >= 256) {
        inflateSetDictionary(&strm, Data, 256);
    }

    cleanupStream(&strm);

    return 0;
}