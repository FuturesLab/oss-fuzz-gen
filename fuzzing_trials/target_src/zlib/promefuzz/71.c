// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DICT_BUFFER_SIZE 32768
#define OUTPUT_BUFFER_SIZE 32768

static void initialize_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    initialize_stream(&strm);

    int level = Data[0] % 10; // Compression level (0-9)
    int method = Z_DEFLATED;
    int windowBits = 15; // Default window size
    int memLevel = 8; // Default memory level
    int strategy = Data[0] % 5; // Strategy (0-4)

    int ret = deflateInit2_(&strm, level, method, windowBits, memLevel, strategy, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    Bytef dictionary[DICT_BUFFER_SIZE];
    uInt dictLength = DICT_BUFFER_SIZE;

    ret = deflateGetDictionary(&strm, dictionary, &dictLength);
    if (ret != Z_OK) goto cleanup;

    ret = deflateSetDictionary(&strm, dictionary, dictLength);
    if (ret != Z_OK) goto cleanup;

    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;
    Bytef output[OUTPUT_BUFFER_SIZE];
    strm.next_out = output;
    strm.avail_out = OUTPUT_BUFFER_SIZE;

    ret = deflate(&strm, Z_NO_FLUSH);
    if (ret != Z_OK && ret != Z_BUF_ERROR) goto cleanup;

    ret = deflatePrime(&strm, 3, Data[0] & 0x7);
    if (ret != Z_OK && ret != Z_BUF_ERROR) goto cleanup;

    ret = deflate(&strm, Z_FINISH);
    if (ret != Z_STREAM_END && ret != Z_OK && ret != Z_BUF_ERROR) goto cleanup;

cleanup:
    deflateEnd(&strm);
    return 0;
}