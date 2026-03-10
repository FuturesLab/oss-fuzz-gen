#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

static void initialize_z_stream(z_stream *strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void initialize_gz_header(gz_header *header) {
    memset(header, 0, sizeof(gz_header));
    header->extra = Z_NULL;
    header->name = Z_NULL;
    header->comment = Z_NULL;
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_z_stream(&strm);

    int windowBits = (Data[0] % 16) - 8; // Window size from -8 to 7
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    int ret = inflateInit2_(&strm, windowBits, version, stream_size);
    if (ret == Z_OK) {
        inflateReset(&strm);
        inflateReset2(&strm, windowBits);
        inflateResetKeep(&strm);
        deflateResetKeep(&strm);

        gz_header header;
        initialize_gz_header(&header);
        inflateGetHeader(&strm, &header);

        inflateEnd(&strm);
    }

    return 0;
}