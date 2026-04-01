// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateBackInit_ at infback.c:25:13 in zlib.h
// inflateBack at infback.c:191:13 in zlib.h
// inflateBackEnd at infback.c:574:13 in zlib.h
// inflateInit2_ at inflate.c:173:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateSyncPoint at inflate.c:1320:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zlib.h"

static unsigned int dummy_in_func(void *in_desc, unsigned char **buf) {
    *buf = (unsigned char *)in_desc;
    return 1; // Return 1 byte to process
}

static int dummy_out_func(void *out_desc, unsigned char *buf, unsigned len) {
    (void)out_desc;
    (void)buf;
    (void)len;
    return Z_OK;
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    unsigned char window[32768]; // 32K window size for inflateBackInit_

    // Initialize inflateBack
    if (inflateBackInit_(&strm, 15, window, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // Test inflateBack
    inflateBack(&strm, dummy_in_func, (void *)Data, dummy_out_func, NULL);

    // Cleanup
    inflateBackEnd(&strm);

    // Reinitialize for inflate
    if (inflateInit2_(&strm, 15, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // Set input data
    strm.next_in = Data;
    strm.avail_in = Size;

    // Prepare output buffer
    unsigned char out_buffer[32768];
    strm.next_out = out_buffer;
    strm.avail_out = sizeof(out_buffer);

    // Test inflate
    inflate(&strm, Z_NO_FLUSH);

    // Check sync point
    inflateSyncPoint(&strm);

    // Set dictionary if possible
    if (Size > 2) {
        inflateSetDictionary(&strm, Data, 2);
    }

    // Cleanup
    inflateEnd(&strm);

    return 0;
}