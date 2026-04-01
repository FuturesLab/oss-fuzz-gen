// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:92:15 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress_z at compress.c:73:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress2 at compress.c:63:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress at compress.c:78:13 in zlib.h
// uncompress at uncompr.c:93:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <zlib.h>

static void fuzz_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    z_size_t destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int level = Data[0] % 10; // Compression level between 0 and 9

    int result = compress2_z(dest, &destLen, Data, Size, level);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

static void fuzz_compress_z(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    z_size_t destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress_z(dest, &destLen, Data, Size);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

static void fuzz_compress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int level = Data[0] % 10; // Compression level between 0 and 9

    int result = compress2(dest, &destLen, Data, Size, level);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

static void fuzz_compress(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress(dest, &destLen, Data, Size);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

static void fuzz_uncompress(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    uLongf destLen = Size * 2; // Arbitrary initial size
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = uncompress(dest, &destLen, Data, Size);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_compress_z(Data, Size);
    fuzz_compress2(Data, Size);
    fuzz_compress(Data, Size);
    fuzz_uncompress(Data, Size);

    return 0;
}