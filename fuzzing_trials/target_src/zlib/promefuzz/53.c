// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// uncompress at uncompr.c:93:13 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// uncompress_z at uncompr.c:88:13 in zlib.h
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

static void fuzz_uncompress(const uint8_t *Data, size_t Size) {
    uLongf destLen = Size * 2; // Assume decompressed data might be twice the size
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int result = uncompress(dest, &destLen, Data, Size);

    // Handle result if necessary
    free(dest);
}

static void fuzz_uncompress2(const uint8_t *Data, size_t Size) {
    uLongf destLen = Size * 2;
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    uLong sourceLen = Size;
    int result = uncompress2(dest, &destLen, Data, &sourceLen);

    // Handle result if necessary
    free(dest);
}

static void fuzz_uncompress_z(const uint8_t *Data, size_t Size) {
    z_size_t destLen = Size * 2;
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    int result = uncompress_z(dest, &destLen, Data, Size);

    // Handle result if necessary
    free(dest);
}

static void fuzz_uncompress2_z(const uint8_t *Data, size_t Size) {
    z_size_t destLen = Size * 2;
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return;

    z_size_t sourceLen = Size;
    int result = uncompress2_z(dest, &destLen, Data, &sourceLen);

    // Handle result if necessary
    free(dest);
}

static void fuzz_inflateSetDictionary(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    if (inflateInit(&strm) != Z_OK) return;

    int result = inflateSetDictionary(&strm, Data, Size);

    // Handle result if necessary
    inflateEnd(&strm);
}

static void fuzz_inflateSync(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    if (inflateInit(&strm) != Z_OK) return;

    strm.next_in = (z_const Bytef *)Data;
    strm.avail_in = Size;

    int result = inflateSync(&strm);

    // Handle result if necessary
    inflateEnd(&strm);
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    fuzz_uncompress(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_uncompress_z(Data, Size);
    fuzz_uncompress2_z(Data, Size);
    fuzz_inflateSetDictionary(Data, Size);
    fuzz_inflateSync(Data, Size);

    return 0;
}