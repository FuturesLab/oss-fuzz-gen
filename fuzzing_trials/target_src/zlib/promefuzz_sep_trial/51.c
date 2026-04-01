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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void fuzz_uncompress_z(const uint8_t *Data, size_t Size) {
    Bytef dest[1024];
    z_size_t destLen = sizeof(dest);
    int ret = uncompress_z(dest, &destLen, Data, Size);
    if (ret != Z_OK) {
        // Handle error or log
    }
}

static void fuzz_uncompress2(const uint8_t *Data, size_t Size) {
    Bytef dest[1024];
    uLongf destLen = sizeof(dest);
    uLong sourceLen = Size;
    int ret = uncompress2(dest, &destLen, Data, &sourceLen);
    if (ret != Z_OK) {
        // Handle error or log
    }
}

static void fuzz_inflateSetDictionary(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    if (inflateInit(&strm) != Z_OK) {
        return;
    }
    int ret = inflateSetDictionary(&strm, Data, Size);
    if (ret != Z_OK) {
        // Handle error or log
    }
    inflateEnd(&strm);
}

static void fuzz_uncompress(const uint8_t *Data, size_t Size) {
    Bytef dest[1024];
    uLongf destLen = sizeof(dest);
    int ret = uncompress(dest, &destLen, Data, Size);
    if (ret != Z_OK) {
        // Handle error or log
    }
}

static void fuzz_inflateSync(const uint8_t *Data, size_t Size) {
    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    if (inflateInit(&strm) != Z_OK) {
        return;
    }
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;
    int ret = inflateSync(&strm);
    if (ret != Z_OK) {
        // Handle error or log
    }
    inflateEnd(&strm);
}

static void fuzz_uncompress2_z(const uint8_t *Data, size_t Size) {
    Bytef dest[1024];
    z_size_t destLen = sizeof(dest);
    z_size_t sourceLen = Size;
    int ret = uncompress2_z(dest, &destLen, Data, &sourceLen);
    if (ret != Z_OK) {
        // Handle error or log
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    fuzz_uncompress_z(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_inflateSetDictionary(Data, Size);
    fuzz_uncompress(Data, Size);
    fuzz_inflateSync(Data, Size);
    fuzz_uncompress2_z(Data, Size);
    return 0;
}