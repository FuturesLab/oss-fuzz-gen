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

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);
    int ret = inflateInit(&strm);
    if (ret != Z_OK) return 0;

    z_stream strm_copy;
    initialize_stream(&strm_copy);

    uint8_t dummy_out[256];
    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;
    strm.next_out = dummy_out;
    strm.avail_out = sizeof(dummy_out);

    int bits = Data[0] & 0x1F; // Use first byte for bits
    int value = Data[0] >> 5;  // Use remaining bits for value

    // Call inflatePrime
    inflatePrime(&strm, bits, value);

    // Call inflateSync
    inflateSync(&strm);

    // Call inflate
    inflate(&strm, Z_NO_FLUSH);

    // Call inflateSync again
    inflateSync(&strm);

    // Call inflateSyncPoint
    inflateSyncPoint(&strm);

    // Call inflateCopy
    inflateCopy(&strm_copy, &strm);

    // Call inflateUndermine
    inflateUndermine(&strm, 1);

    // Call inflateMark
    inflateMark(&strm);

    // Call inflateEnd
    inflateEnd(&strm);
    inflateEnd(&strm_copy);

    return 0;
}