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

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
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
        deflatePrime(&strm, bitsToPrime, value);
    }

    // Cleanup the deflate stream

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from deflatePending to deflateTune
    int ret_gzclose_zkoxy = gzclose(0);
    if (ret_gzclose_zkoxy < 0){
    	return 0;
    }

    int ret_deflateTune_owick = deflateTune(0, Z_TREES, ret_gzclose_zkoxy, bits, Z_HUFFMAN_ONLY);
    if (ret_deflateTune_owick < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    deflateEnd(&strm);

    // Write dummy file
    write_dummy_file(Data, Size);

    return 0;
}