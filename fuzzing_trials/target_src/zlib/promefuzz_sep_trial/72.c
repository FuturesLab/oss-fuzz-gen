// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateGetDictionary at deflate.c:626:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    // Initialize the zlib stream
    int level = Z_DEFAULT_COMPRESSION;
    int method = Z_DEFLATED;
    int windowBits = 15;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    if (deflateInit2_(&strm, level, method, windowBits, memLevel, strategy, version, stream_size) != Z_OK) {
        return 0;
    }

    // Use a portion of the input data as a dictionary
    uInt dictLength = Size > 32768 ? 32768 : (uInt)Size;
    deflateSetDictionary(&strm, Data, dictLength);

    // Prepare output buffer
    uInt outBufferSize = 32768;
    Bytef *outBuffer = (Bytef *)malloc(outBufferSize);
    if (!outBuffer) {
        deflateEnd(&strm);
        return 0;
    }

    // Set input data
    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;

    // Set output data
    strm.next_out = outBuffer;
    strm.avail_out = outBufferSize;

    // Perform compression
    int flush = Z_NO_FLUSH;
    deflate(&strm, flush);

    // Get dictionary
    Bytef dictionary[32768];
    uInt dictionaryLength = 0;
    deflateGetDictionary(&strm, dictionary, &dictionaryLength);

    // Prime the deflate stream with some bits
    if (Size > 1) {
        int bits = Data[0] % 8;
        int value = Data[1];
        deflatePrime(&strm, bits, value);
    }

    // Finalize compression
    flush = Z_FINISH;
    deflate(&strm, flush);

    // Cleanup
    deflateEnd(&strm);
    free(outBuffer);

    return 0;
}