// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflatePrime at inflate.c:219:13 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflateSyncPoint at inflate.c:1320:13 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
// inflateUndermine at inflate.c:1370:13 in zlib.h
// inflateMark at inflate.c:1397:14 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void initialize_stream(z_stream *strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    z_stream strm;
    initialize_stream(&strm);

    uint8_t out_buffer[256];
    strm.next_in = (z_const Bytef *)Data;
    strm.avail_in = Size;
    strm.next_out = out_buffer;
    strm.avail_out = sizeof(out_buffer);

    if (inflateInit(&strm) != Z_OK) {
        return 0;
    }

    // Attempt to manipulate the bit stream
    inflatePrime(&strm, 5, 31);

    // Synchronize the stream to recover from potential errors
    inflateSync(&strm);

    // Decompress data
    inflate(&strm, Z_NO_FLUSH);

    // Synchronize again
    inflateSync(&strm);

    // Check synchronization point
    inflateSyncPoint(&strm);

    // Copy the stream state
    z_stream dest_strm;
    initialize_stream(&dest_strm);
    inflateCopy(&dest_strm, &strm);

    // Manage decompression integrity
    inflateUndermine(&strm, 1);

    // Retrieve marker
    inflateMark(&strm);

    // Clean up
    inflateEnd(&strm);
    inflateEnd(&dest_strm);

    return 0;
}