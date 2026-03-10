// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
// inflateReset2 at inflate.c:136:13 in zlib.h
// inflateBackEnd at infback.c:574:13 in zlib.h
// inflateUndermine at inflate.c:1370:13 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
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
    inflateInit(strm);
}

static void cleanup_stream(z_streamp strm) {
    inflateEnd(strm);
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream source, dest;
    initialize_stream(&source);
    initialize_stream(&dest);

    // Fuzz inflateCopy
    inflateCopy(&dest, &source);

    // Fuzz inflateReset2 with random windowBits
    int windowBits = (int)(Data[0] % 16) + 8; // windowBits range from 8 to 15
    inflateReset2(&source, windowBits);

    // Fuzz inflateBackEnd
    inflateBackEnd(&source);

    // Fuzz inflateUndermine with random subvert
    int subvert = Data[0] % 2; // subvert is either 0 or 1
    inflateUndermine(&source, subvert);

    // Fuzz inflateSync
    inflateSync(&source);

    // Fuzz inflate with random flush
    int flush = Data[0] % 6; // flush is between 0 and 5
    source.next_in = (Bytef *)Data;
    source.avail_in = (uInt)Size;
    source.next_out = (Bytef *)malloc(Size);
    source.avail_out = (uInt)Size;
    inflate(&source, flush);

    free(source.next_out);
    cleanup_stream(&source);
    cleanup_stream(&dest);

    return 0;
}