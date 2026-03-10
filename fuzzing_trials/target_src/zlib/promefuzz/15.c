// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateBound_z at deflate.c:857:18 in zlib.h
// compressBound_z at compress.c:87:18 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// deflateBound at deflate.c:930:15 in zlib.h
// compressBound_z at compress.c:87:18 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress at compress.c:78:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void test_deflateBound_z(z_streamp strm, z_size_t sourceLen) {
    z_size_t result = deflateBound_z(strm, sourceLen);
    (void)result; // Suppress unused variable warning
}

static void test_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    z_size_t destLen = compressBound_z(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int level = Data[0] % 10; // Compression level range 0-9
    int result = compress2_z(dest, &destLen, Data, Size, level);
    (void)result; // Suppress unused variable warning

    free(dest);
}

static void test_deflateBound(z_streamp strm, uLong sourceLen) {
    uLong result = deflateBound(strm, sourceLen);
    (void)result; // Suppress unused variable warning
}

static void test_compressBound_z(z_size_t sourceLen) {
    z_size_t result = compressBound_z(sourceLen);
    (void)result; // Suppress unused variable warning
}

static void test_compress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress(dest, &destLen, Data, Size);
    (void)result; // Suppress unused variable warning

    free(dest);
}

static void test_compressBound(uLong sourceLen) {
    uLong result = compressBound(sourceLen);
    (void)result; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    // Test each function with the provided data
    test_deflateBound_z(&strm, Size);
    test_compress2_z(Data, Size);
    test_deflateBound(&strm, (uLong)Size);
    test_compressBound_z(Size);
    test_compress(Data, Size);
    test_compressBound((uLong)Size);

    return 0;
}