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
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

static void test_deflateBound_z(z_streamp strm, z_size_t sourceLen) {
    z_size_t bound = deflateBound_z(strm, sourceLen);
    (void)bound; // Use the result to suppress unused variable warning
}

static void test_compress2_z(const Bytef *source, z_size_t sourceLen, int level) {
    z_size_t destLen = compressBound_z(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest) {
        int result = compress2_z(dest, &destLen, source, sourceLen, level);
        (void)result; // Use the result to suppress unused variable warning
        free(dest);
    }
}

static void test_compress_z(const Bytef *source, z_size_t sourceLen) {
    z_size_t destLen = compressBound_z(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest) {
        int result = compress_z(dest, &destLen, source, sourceLen);
        (void)result; // Use the result to suppress unused variable warning
        free(dest);
    }
}

static void test_deflateBound(z_streamp strm, uLong sourceLen) {
    uLong bound = deflateBound(strm, sourceLen);
    (void)bound; // Use the result to suppress unused variable warning
}

static void test_compressBound_z(z_size_t sourceLen) {
    z_size_t bound = compressBound_z(sourceLen);
    (void)bound; // Use the result to suppress unused variable warning
}

static void test_compressBound(uLong sourceLen) {
    uLong bound = compressBound(sourceLen);
    (void)bound; // Use the result to suppress unused variable warning
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    z_stream strm;
    strm.next_in = Data;
    strm.avail_in = (uInt)Size;
    strm.total_in = 0;
    strm.next_out = NULL;
    strm.avail_out = 0;
    strm.total_out = 0;
    strm.msg = NULL;
    strm.state = NULL;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.data_type = 0;
    strm.adler = 0;
    strm.reserved = 0;

    if (Size > 0) {
        test_deflateBound_z(&strm, (z_size_t)Size);
        test_compress2_z(Data, (z_size_t)Size, Z_DEFAULT_COMPRESSION);
        test_compress_z(Data, (z_size_t)Size);
        test_deflateBound(&strm, (uLong)Size);
        test_compressBound_z((z_size_t)Size);
        test_compressBound((uLong)Size);
    }

    return 0;
}