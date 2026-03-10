// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// uncompress_z at uncompr.c:88:13 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// uncompress at uncompr.c:93:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// uncompress2_z at uncompr.c:29:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define MAX_BUFFER_SIZE 1024 * 1024

static void test_uncompress_z(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    z_size_t destLen = MAX_BUFFER_SIZE;
    uncompress_z(dest, &destLen, Data, Size);
}

static void test_uncompress2(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    uLongf destLen = MAX_BUFFER_SIZE;
    uLong sourceLen = Size;
    uncompress2(dest, &destLen, Data, &sourceLen);
}

static void test_inflateSetDictionary(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    inflateInit(&strm);
    inflateSetDictionary(&strm, Data, Size > 32768 ? 32768 : Size);
    inflateEnd(&strm);
}

static void test_uncompress(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    uLongf destLen = MAX_BUFFER_SIZE;
    uncompress(dest, &destLen, Data, Size);
}

static void test_inflateSync(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    inflateInit(&strm);
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;
    inflateSync(&strm);
    inflateEnd(&strm);
}

static void test_uncompress2_z(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    z_size_t destLen = MAX_BUFFER_SIZE;
    z_size_t sourceLen = Size;
    uncompress2_z(dest, &destLen, Data, &sourceLen);
}

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    test_uncompress_z(Data, Size);
    test_uncompress2(Data, Size);
    test_inflateSetDictionary(Data, Size);
    test_uncompress(Data, Size);
    test_inflateSync(Data, Size);
    test_uncompress2_z(Data, Size);
    return 0;
}