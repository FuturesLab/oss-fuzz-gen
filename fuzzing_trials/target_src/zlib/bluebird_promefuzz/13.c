#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"

static void initialize_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = Z_NULL;
    strm->avail_in = 0;
}

static void test_inflateCopy(z_streamp source) {
    z_stream dest;
    initialize_z_stream(&dest);
    int ret = inflateCopy(&dest, source);
    if (ret == Z_OK) {
        inflateEnd(&dest);
    }
}

static void test_inflate(z_streamp strm) {
    int ret;
    do {
        ret = inflate(strm, Z_NO_FLUSH);
    } while (ret == Z_OK);
}

static void test_inflateGetDictionary(z_streamp strm) {
    uInt dictLength;
    if (inflateGetDictionary(strm, NULL, &dictLength) == Z_OK && dictLength > 0) {
        Bytef *dictionary = (Bytef *)malloc(dictLength);
        if (dictionary) {
            inflateGetDictionary(strm, dictionary, &dictLength);
            free(dictionary);
        }
    }
}

static void test_inflateSync(z_streamp strm) {
    inflateSync(strm);
}

static void test_inflateSetDictionary(z_streamp strm) {
    const Bytef dictionary[] = "sample dictionary";
    inflateSetDictionary(strm, dictionary, sizeof(dictionary));
}

static void test_deflateSetDictionary(z_streamp strm) {
    const Bytef dictionary[] = "sample dictionary";
    deflateSetDictionary(strm, dictionary, sizeof(dictionary));
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    z_stream strm;
    initialize_z_stream(&strm);

    if (inflateInit(&strm) != Z_OK) {
        return 0;
    }

    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;

    Bytef out[256];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    test_inflateCopy(&strm);
    test_inflate(&strm);
    test_inflateGetDictionary(&strm);
    test_inflateSync(&strm);
    test_inflateSetDictionary(&strm);
    test_deflateSetDictionary(&strm);

    inflateEnd(&strm);
    return 0;
}