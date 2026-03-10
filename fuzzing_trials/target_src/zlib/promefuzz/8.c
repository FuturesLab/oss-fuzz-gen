// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateBound_z at deflate.c:857:18 in zlib.h
// compressBound_z at compress.c:87:18 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// compressBound_z at compress.c:87:18 in zlib.h
// compress_z at compress.c:73:13 in zlib.h
// deflateBound at deflate.c:930:15 in zlib.h
// compressBound_z at compress.c:87:18 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void test_deflateBound_z(z_streamp strm, z_size_t sourceLen) {
    z_size_t bound = deflateBound_z(strm, sourceLen);
    (void)bound; // Suppress unused variable warning
}

static void test_compress2_z(const Bytef *source, z_size_t sourceLen, int level) {
    z_size_t destLen = compressBound_z(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int result = compress2_z(dest, &destLen, source, sourceLen, level);
    (void)result; // Suppress unused variable warning
    free(dest);
}

static void test_compress_z(const Bytef *source, z_size_t sourceLen) {
    z_size_t destLen = compressBound_z(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int result = compress_z(dest, &destLen, source, sourceLen);
    (void)result; // Suppress unused variable warning
    free(dest);
}

static void test_deflateBound(z_streamp strm, uLong sourceLen) {
    uLong bound = deflateBound(strm, sourceLen);
    (void)bound; // Suppress unused variable warning
}

static void test_compressBound_z(z_size_t sourceLen) {
    z_size_t bound = compressBound_z(sourceLen);
    (void)bound; // Suppress unused variable warning
}

static void test_compressBound(uLong sourceLen) {
    uLong bound = compressBound(sourceLen);
    (void)bound; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    test_deflateBound_z(&strm, Size);
    test_compress2_z(Data, Size, Z_DEFAULT_COMPRESSION);
    test_compress_z(Data, Size);
    test_deflateBound(&strm, Size);
    test_compressBound_z(Size);
    test_compressBound(Size);

    return 0;
}