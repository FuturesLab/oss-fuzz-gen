#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

static void fuzz_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    z_size_t destLen = compressBound_z(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int level = Data[0] % 10; // Compression level between 0-9
    int result = compress2_z(dest, &destLen, Data, Size, level);

    if (result == Z_OK) {
        // Optionally, test decompression if compression was successful
        uLongf uncompressedLen = Size;
        Bytef *uncompressed = (Bytef *)malloc(uncompressedLen);
        if (uncompressed != NULL) {
            uncompress(uncompressed, &uncompressedLen, dest, destLen);
            free(uncompressed);
        }
    }

    free(dest);
}

static void fuzz_compress_z(const uint8_t *Data, size_t Size) {
    z_size_t destLen = compressBound_z(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int result = compress_z(dest, &destLen, Data, Size);

    if (result == Z_OK) {
        // Optionally, test decompression if compression was successful
        uLongf uncompressedLen = Size;
        Bytef *uncompressed = (Bytef *)malloc(uncompressedLen);
        if (uncompressed != NULL) {
            uncompress(uncompressed, &uncompressedLen, dest, destLen);
            free(uncompressed);
        }
    }

    free(dest);
}

static void fuzz_compress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int level = Data[0] % 10; // Compression level between 0-9
    int result = compress2(dest, &destLen, Data, Size, level);

    if (result == Z_OK) {
        // Optionally, test decompression if compression was successful
        uLongf uncompressedLen = Size;
        Bytef *uncompressed = (Bytef *)malloc(uncompressedLen);
        if (uncompressed != NULL) {
            uncompress(uncompressed, &uncompressedLen, dest, destLen);
            free(uncompressed);
        }
    }

    free(dest);
}

static void fuzz_compress(const uint8_t *Data, size_t Size) {
    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int result = compress(dest, &destLen, Data, Size);

    if (result == Z_OK) {
        // Optionally, test decompression if compression was successful
        uLongf uncompressedLen = Size;
        Bytef *uncompressed = (Bytef *)malloc(uncompressedLen);
        if (uncompressed != NULL) {
            uncompress(uncompressed, &uncompressedLen, dest, destLen);
            free(uncompressed);
        }
    }

    free(dest);
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_compress_z(Data, Size);
    fuzz_compress2(Data, Size);
    fuzz_compress(Data, Size);
    return 0;
}