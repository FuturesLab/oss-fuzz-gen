// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:380:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateParams at deflate.c:775:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
// deflateParams at deflate.c:775:13 in zlib.h
// deflate at deflate.c:982:13 in zlib.h
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
#include <string.h>
#include <zlib.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    int level = Z_DEFAULT_COMPRESSION;
    int strategy = Z_DEFAULT_STRATEGY;
    int flush = Z_NO_FLUSH;

    // Prepare input and output buffers
    Bytef *input = (Bytef *)Data;
    uInt input_size = Size;
    Bytef output[1024];
    uInt output_size = sizeof(output);

    // Initialize the deflate stream
    if (deflateInit_(&strm, level, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // First deflate call
    strm.next_in = input;
    strm.avail_in = input_size;
    strm.next_out = output;
    strm.avail_out = output_size;
    deflate(&strm, flush);

    // First deflateParams call
    deflateParams(&strm, level, strategy);

    // Second deflate call
    strm.next_in = input;
    strm.avail_in = input_size;
    strm.next_out = output;
    strm.avail_out = output_size;
    deflate(&strm, flush);

    // Second deflateParams call
    deflateParams(&strm, level, strategy);

    // Third deflate call
    strm.next_in = input;
    strm.avail_in = input_size;
    strm.next_out = output;
    strm.avail_out = output_size;
    deflate(&strm, flush);

    // Fourth deflate call
    strm.next_in = input;
    strm.avail_in = input_size;
    strm.next_out = output;
    strm.avail_out = output_size;
    deflate(&strm, flush);

    // Clean up
    deflateEnd(&strm);

    return 0;
}