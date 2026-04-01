// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateGetDictionary at inflate.c:1167:13 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateReset2 at inflate.c:136:13 in zlib.h
// inflateInit2_ at inflate.c:173:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
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

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

static void test_inflateGetDictionary(z_streamp strm) {
    Bytef dictionary[1024];
    uInt dictLength = sizeof(dictionary);
    int result = inflateGetDictionary(strm, dictionary, &dictLength);
    if (result != Z_OK) {
        fprintf(stderr, "inflateGetDictionary failed: %d\n", result);
    }
}

static void test_inflateCopy(z_streamp source) {
    z_stream dest;
    initialize_stream(&dest);
    int result = inflateCopy(&dest, source);
    if (result != Z_OK) {
        fprintf(stderr, "inflateCopy failed: %d\n", result);
    }
    inflateEnd(&dest);
}

static void test_inflate(z_streamp strm) {
    int result = inflate(strm, Z_NO_FLUSH);
    if (result != Z_OK && result != Z_STREAM_END) {
        fprintf(stderr, "inflate failed: %d\n", result);
    }
}

static void test_inflateReset2(z_streamp strm, int windowBits) {
    int result = inflateReset2(strm, windowBits);
    if (result != Z_OK) {
        fprintf(stderr, "inflateReset2 failed: %d\n", result);
    }
}

static void test_inflateInit2(z_streamp strm, int windowBits) {
    int result = inflateInit2_(strm, windowBits, ZLIB_VERSION, sizeof(z_stream));
    if (result != Z_OK) {
        fprintf(stderr, "inflateInit2_ failed: %d\n", result);
    }
}

static void test_deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength) {
    int result = deflateSetDictionary(strm, dictionary, dictLength);
    if (result != Z_OK) {
        fprintf(stderr, "deflateSetDictionary failed: %d\n", result);
    }
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    // Test inflateInit2_
    test_inflateInit2(&strm, MAX_WBITS);

    // Test inflateGetDictionary
    test_inflateGetDictionary(&strm);

    // Test inflateCopy
    test_inflateCopy(&strm);

    // Test inflate
    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;
    Bytef out[1024];
    strm.next_out = out;
    strm.avail_out = sizeof(out);
    test_inflate(&strm);

    // Test inflateReset2
    test_inflateReset2(&strm, MAX_WBITS);

    // Test deflateSetDictionary
    if (Size > 10) {
        test_deflateSetDictionary(&strm, Data, 10);
    }

    inflateEnd(&strm);

    return 0;
}