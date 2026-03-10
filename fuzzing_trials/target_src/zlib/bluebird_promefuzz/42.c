#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"

#define DUMMY_FILE "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    } // Ensure there is enough data

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    int level = Data[0] % 10; // Compression level
    int method = Z_DEFLATED; // Compression method
    int windowBits = 15; // Default window size
    int memLevel = 8; // Default memory level
    int strategy = Z_DEFAULT_STRATEGY; // Default strategy
    const char *version = ZLIB_VERSION;
    int stream_size = sizeof(z_stream);

    // Initialize the deflate stream
    int ret = deflateInit2_(&strm, level, method, windowBits, memLevel, strategy, version, stream_size);
    if (ret != Z_OK) {
        return 0;
    }

    // Prepare dummy input and output buffers
    Bytef input[128];
    Bytef output[128];
    strm.next_in = input;
    strm.avail_in = sizeof(input);
    strm.next_out = output;
    strm.avail_out = sizeof(output);

    // Set dictionary if possible
    if (Size > 2) {
        uInt dictLength = Data[1] % (Size - 2); // Ensure dictLength is within bounds
        deflateSetDictionary(&strm, Data + 2, dictLength);
    }

    // Get dictionary
    Bytef dictionary[128];
    uInt dictLength = sizeof(dictionary);
    deflateGetDictionary(&strm, dictionary, &dictLength);

    // Check pending output
    unsigned pending;
    int bits;
    deflatePending(&strm, &pending, &bits);

    // Prime some bits
    if (Size > 3) {
        int bitsToPrime = Data[2] % 16;
        int value = Data[3];

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function deflatePrime with deflateParams
        deflateParams(&strm, bitsToPrime, value);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Cleanup the deflate stream
    deflateEnd(&strm);

    // Write dummy file
    write_dummy_file(Data, Size);

    return 0;
}