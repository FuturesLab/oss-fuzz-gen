#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void initialize_stream(z_stream *strm, const uint8_t *Data, size_t Size) {
    memset(strm, 0, sizeof(z_stream));
    strm->next_in = Data;
    strm->avail_in = Size;
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void initialize_header(gz_header *head) {
    memset(head, 0, sizeof(gz_header));
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm, Data, Size);

    gz_header head;
    initialize_header(&head);

    int ret = inflateInit2_(&strm, MAX_WBITS + 16, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    ret = inflateGetHeader(&strm, &head);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    unsigned char out[1024];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_OK && ret != Z_STREAM_END) {
        inflateEnd(&strm);
        return 0;
    }

    const Bytef dict[] = "dummy_dictionary";
    ret = inflateSetDictionary(&strm, dict, sizeof(dict));
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflate(&strm, Z_FINISH);
    if (ret != Z_OK && ret != Z_STREAM_END) {
        inflateEnd(&strm);
        return 0;
    }

    z_stream copy;
    initialize_stream(&copy, NULL, 0);

    ret = inflateCopy(&copy, &strm);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateEnd(&copy);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateReset2(&strm, MAX_WBITS);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateEnd(&strm);
    return 0;
}