// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:92:15 in zlib.h
// uncompress at uncompr.c:93:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// uncompress_z at uncompr.c:88:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// uncompress2_z at uncompr.c:29:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateSync at inflate.c:1264:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static int fuzz_uncompress(const uint8_t *Data, size_t Size) {
    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return 0;

    int ret = uncompress(dest, &destLen, Data, Size);
    free(dest);
    return ret;
}

static int fuzz_uncompress2(const uint8_t *Data, size_t Size) {
    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return 0;

    uLong sourceLen = Size;
    int ret = uncompress2(dest, &destLen, Data, &sourceLen);
    free(dest);
    return ret;
}

static int fuzz_uncompress_z(const uint8_t *Data, size_t Size) {
    z_size_t destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return 0;

    int ret = uncompress_z(dest, &destLen, Data, Size);
    free(dest);
    return ret;
}

static int fuzz_uncompress2_z(const uint8_t *Data, size_t Size) {
    z_size_t destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return 0;

    z_size_t sourceLen = Size;
    int ret = uncompress2_z(dest, &destLen, Data, &sourceLen);
    free(dest);
    return ret;
}

static int fuzz_inflateSetDictionary(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    inflateInit(&strm);

    int ret = inflateSetDictionary(&strm, Data, Size);
    inflateEnd(&strm);
    return ret;
}

static int fuzz_inflateSync(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    inflateInit(&strm);

    strm.next_in = (z_const Bytef *)Data;
    strm.avail_in = Size;

    int ret = inflateSync(&strm);
    inflateEnd(&strm);
    return ret;
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    fuzz_uncompress(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_uncompress_z(Data, Size);
    fuzz_uncompress2_z(Data, Size);
    fuzz_inflateSetDictionary(Data, Size);
    fuzz_inflateSync(Data, Size);

    return 0;
}