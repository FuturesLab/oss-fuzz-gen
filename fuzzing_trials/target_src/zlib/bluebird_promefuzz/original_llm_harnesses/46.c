// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// zlibCompileFlags at zutil.c:31:15 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// uncompress at uncompr.c:93:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress2 at compress.c:63:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress at compress.c:78:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void test_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLong sourceLen = Size;
    uLong destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int level = Data[0] % 10; // Compression level between 0 and 9
    int result = compress2_z(dest, &destLen, Data, sourceLen, level);

    if (result != Z_OK) {
        fprintf(stderr, "compress2_z failed: %d\n", result);
    }

    free(dest);
}

static void test_uncompress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLong sourceLen = Size;
    uLongf destLen = sourceLen * 2; // Assume decompressed data is at most twice the size
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = uncompress2(dest, &destLen, Data, &sourceLen);

    if (result != Z_OK) {
        fprintf(stderr, "uncompress2 failed: %d\n", result);
    }

    free(dest);
}

static void test_uncompress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLong sourceLen = Size;
    uLongf destLen = sourceLen * 2; // Assume decompressed data is at most twice the size
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = uncompress(dest, &destLen, Data, sourceLen);

    if (result != Z_OK) {
        fprintf(stderr, "uncompress failed: %d\n", result);
    }

    free(dest);
}

static void test_compress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLong sourceLen = Size;
    uLong destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int level = Data[0] % 10; // Compression level between 0 and 9
    int result = compress2(dest, &destLen, Data, sourceLen, level);

    if (result != Z_OK) {
        fprintf(stderr, "compress2 failed: %d\n", result);
    }

    free(dest);
}

static void test_compress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLong sourceLen = Size;
    uLong destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress(dest, &destLen, Data, sourceLen);

    if (result != Z_OK) {
        fprintf(stderr, "compress failed: %d\n", result);
    }

    free(dest);
}

static void test_zlibCompileFlags() {
    uLong flags = zlibCompileFlags();
    printf("zlibCompileFlags: %lu\n", flags);
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    test_compress2_z(Data, Size);
    test_uncompress2(Data, Size);
    test_uncompress(Data, Size);
    test_compress2(Data, Size);
    test_compress(Data, Size);
    test_zlibCompileFlags();
    return 0;
}