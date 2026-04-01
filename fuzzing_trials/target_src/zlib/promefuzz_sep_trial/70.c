// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void init_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    init_stream(&strm);

    int level = Data[0] % 10; // Compression level between 0-9
    int method = Z_DEFLATED;
    int windowBits = 15;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    int ret = deflateInit2_(&strm, level, method, windowBits, memLevel, strategy, version, stream_size);
    if (ret != Z_OK) return 0;

    // Prepare input and output buffers
    Bytef *input = (Bytef *)Data;
    uInt inputLength = (uInt)Size;
    Bytef output[4096];
    uInt outputLength = sizeof(output);

    strm.next_in = input;
    strm.avail_in = inputLength;
    strm.next_out = output;
    strm.avail_out = outputLength;

    // Fuzz deflate function
    int flush = Z_NO_FLUSH;
    ret = deflate(&strm, flush);
    if (ret != Z_OK && ret != Z_STREAM_END) {
        deflateEnd(&strm);
        return 0;
    }

    // Fuzz deflateSetDictionary function
    if (Size > 1) {
        uInt dictLength = (uInt)(Size - 1);
        ret = deflateSetDictionary(&strm, input + 1, dictLength);
        if (ret != Z_OK) {
            deflateEnd(&strm);
            return 0;
        }
    }

    // Fuzz deflatePrime function
    if (Size > 2) {
        int bits = Data[1] % 16; // Up to 15 bits
        int value = Data[2];
        ret = deflatePrime(&strm, bits, value);
        if (ret != Z_OK) {
            deflateEnd(&strm);
            return 0;
        }
    }

    // Fuzz deflateGetDictionary function
    Bytef dictionary[4096];
    uInt dictLength = sizeof(dictionary);
    ret = deflateGetDictionary(&strm, dictionary, &dictLength);
    if (ret != Z_OK) {
        deflateEnd(&strm);
        return 0;
    }

    // Cleanup
    ret = deflateEnd(&strm);
    if (ret != Z_OK) {
        return 0;
    }

    return 0;
}