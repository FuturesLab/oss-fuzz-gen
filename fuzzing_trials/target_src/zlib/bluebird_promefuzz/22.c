#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    deflateInit(strm, Z_DEFAULT_COMPRESSION);
}

static void cleanup_stream(z_streamp strm) {
    deflateEnd(strm);
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    // Setup a dummy gzip header
    gz_header header;
    memset(&header, 0, sizeof(gz_header));
    header.text = 1;
    deflateSetHeader(&strm, &header);

    // Fuzz deflateParams
    int level = Data[0] % 10;  // zlib supports levels 0-9
    int strategy = Data[0] % 5; // assuming 5 different strategies
    deflateParams(&strm, level, strategy);

    // Fuzz deflatePending
    unsigned pending;
    int bits;
    deflatePending(&strm, &pending, &bits);

    // Fuzz deflateCopy
    z_stream dest_strm;
    initialize_stream(&dest_strm);
    deflateCopy(&dest_strm, &strm);

    // Fuzz deflateUsed
    int used_bits;
    deflateUsed(&strm, &used_bits);

    // Fuzz deflateTune
    int good_length = Data[0] % 258; // max good length
    int max_lazy = Data[0] % 258; // max lazy length
    int nice_length = Data[0] % 258; // max nice length
    int max_chain = Data[0] % 4096; // max chain length
    deflateTune(&strm, good_length, max_lazy, nice_length, max_chain);

    cleanup_stream(&strm);
    cleanup_stream(&dest_strm);
    return 0;
}