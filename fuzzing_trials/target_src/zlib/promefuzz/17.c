// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// uncompress at uncompr.c:93:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress_z at compress.c:73:13 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress2 at compress.c:63:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress at compress.c:78:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void fuzz_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    Bytef *dest = NULL;
    z_size_t destLen = compressBound(Size);
    dest = (Bytef *)malloc(destLen);

    if (dest == NULL) return;

    int level = Data[0] % 10; // Compression level between 0 and 9
    int result = compress2_z(dest, &destLen, Data, Size, level);

    if (result == Z_OK) {
        // Do something with compressed data if needed
    }

    free(dest);
}

static void fuzz_compress_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    Bytef *dest = NULL;
    z_size_t destLen = compressBound(Size);
    dest = (Bytef *)malloc(destLen);

    if (dest == NULL) return;

    int result = compress_z(dest, &destLen, Data, Size);

    if (result == Z_OK) {
        // Do something with compressed data if needed
    }

    free(dest);
}

static void fuzz_uncompress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLongf destLen = Size * 2; // Assume the decompressed data will be twice the size
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest == NULL) return;

    uLong sourceLen = Size;
    int result = uncompress2(dest, &destLen, Data, &sourceLen);

    if (result == Z_OK) {
        // Do something with uncompressed data if needed
    }

    free(dest);
}

static void fuzz_compress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    Bytef *dest = NULL;
    uLongf destLen = compressBound(Size);
    dest = (Bytef *)malloc(destLen);

    if (dest == NULL) return;

    int level = Data[0] % 10; // Compression level between 0 and 9
    int result = compress2(dest, &destLen, Data, Size, level);

    if (result == Z_OK) {
        // Do something with compressed data if needed
    }

    free(dest);
}

static void fuzz_compress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    Bytef *dest = NULL;
    uLongf destLen = compressBound(Size);
    dest = (Bytef *)malloc(destLen);

    if (dest == NULL) return;

    int result = compress(dest, &destLen, Data, Size);

    if (result == Z_OK) {
        // Do something with compressed data if needed
    }

    free(dest);
}

static void fuzz_uncompress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLongf destLen = Size * 2; // Assume the decompressed data will be twice the size
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest == NULL) return;

    int result = uncompress(dest, &destLen, Data, Size);

    if (result == Z_OK) {
        // Do something with uncompressed data if needed
    }

    free(dest);
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_compress_z(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_compress2(Data, Size);
    fuzz_compress(Data, Size);
    fuzz_uncompress(Data, Size);

    return 0;
}