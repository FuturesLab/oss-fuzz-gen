#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"

static void setup_stream(z_streamp strm) {
    memset(strm, 0, sizeof(z_stream));
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    z_stream strm;
    setup_stream(&strm);

    int level = Data[0] % 10; // Compression level [0-9]
    int strategy = Data[0] % 5; // Strategy [0-4]
    const char *version = ZLIB_VERSION;
    int stream_size = (int)sizeof(z_stream);

    // Initialize the stream
    if (deflateInit_(&strm, level, version, stream_size) != Z_OK) {
        return 0;
    }

    // Adjust compression parameters
    if (Size > 1) {
        deflateParams(&strm, Data[1] % 10, Data[1] % 5);
    }

    // Tune compression parameters
    if (Size > 5) {
        deflateTune(&strm, Data[2], Data[3], Data[4], Data[5]);
    }

    // Reset the stream
    deflateReset(&strm);

    // Prepare a second stream for copying
    z_stream dest;
    setup_stream(&dest);
    if (deflateInit_(&dest, level, version, stream_size) != Z_OK) {
        deflateEnd(&strm);
        return 0;
    }

    // Copy the stream
    deflateCopy(&dest, &strm);

    // Set up input and output buffers
    Bytef input[1024];
    Bytef output[1024];
    strm.next_in = input;
    strm.avail_in = 0;
    strm.next_out = output;
    strm.avail_out = sizeof(output);

    // Compress data
    if (Size > 6) {
        strm.next_in = (Bytef *)Data;
        strm.avail_in = Size;
        deflate(&strm, Z_FINISH);
    }

    // Clean up

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function deflateEnd with deflateReset
    deflateReset(&strm);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    deflateEnd(&dest);

    return 0;
}