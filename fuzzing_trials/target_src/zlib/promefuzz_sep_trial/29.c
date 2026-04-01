// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateSetHeader at deflate.c:715:13 in zlib.h
// deflateReset at deflate.c:705:13 in zlib.h
// deflatePending at deflate.c:723:13 in zlib.h
// deflateUsed at deflate.c:738:13 in zlib.h
// deflateTune at deflate.c:820:13 in zlib.h
// deflateCopy at deflate.c:1318:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void initialize_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    deflateInit2(strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY);
}

static void cleanup_z_stream(z_streamp strm) {
    deflateEnd(strm);
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(gz_header) + 4 * sizeof(int)) {
        return 0; // Not enough data
    }

    z_stream strm;
    initialize_z_stream(&strm);

    gz_header header;
    memset(&header, 0, sizeof(gz_header));

    // Set header fields using fuzz data
    header.text = Data[0] % 2;
    header.time = *(uLong *)(Data + 1);
    header.xflags = Data[5];
    header.os = Data[6];
    header.extra = (Bytef *)(Data + 7);
    header.extra_len = (Size - 7) > 0 ? (Size - 7) : 0;

    // Fuzzing deflateSetHeader
    deflateSetHeader(&strm, &header);

    // Fuzzing deflateReset
    deflateReset(&strm);

    // Prepare variables for deflatePending
    unsigned pending;
    int bits;
    deflatePending(&strm, &pending, &bits);

    // Fuzzing deflateUsed
    deflateUsed(&strm, &bits);

    // Fuzzing deflateTune
    if (Size >= 7 + 4 * sizeof(int)) {
        int good_length = *(int *)(Data + 7);
        int max_lazy = *(int *)(Data + 7 + sizeof(int));
        int nice_length = *(int *)(Data + 7 + 2 * sizeof(int));
        int max_chain = *(int *)(Data + 7 + 3 * sizeof(int));

        deflateTune(&strm, good_length, max_lazy, nice_length, max_chain);
    }

    // Fuzzing deflateCopy
    z_stream dest_strm;
    initialize_z_stream(&dest_strm);
    deflateCopy(&dest_strm, &strm);
    cleanup_z_stream(&dest_strm);

    cleanup_z_stream(&strm);
    return 0;
}