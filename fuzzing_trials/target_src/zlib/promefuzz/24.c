// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// uncompress2_z at uncompr.c:29:13 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// uncompress at uncompr.c:93:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress at compress.c:78:13 in zlib.h
// uncompress_z at uncompr.c:88:13 in zlib.h
// inflateInit_ at inflate.c:214:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
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

#define MAX_BUFFER_SIZE 1024

static void fuzz_uncompress2_z(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    z_size_t destLen = MAX_BUFFER_SIZE;
    z_size_t sourceLen = Size;

    uncompress2_z(dest, &destLen, Data, &sourceLen);
}

static void fuzz_uncompress2(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    uLongf destLen = MAX_BUFFER_SIZE;
    uLong sourceLen = Size;

    uncompress2(dest, &destLen, Data, &sourceLen);
}

static void fuzz_uncompress(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    uLongf destLen = MAX_BUFFER_SIZE;

    uncompress(dest, &destLen, Data, Size);
}

static void fuzz_compress(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    uLongf destLen = compressBound(Size);

    compress(dest, &destLen, Data, Size);
}

static void fuzz_uncompress_z(const uint8_t *Data, size_t Size) {
    Bytef dest[MAX_BUFFER_SIZE];
    z_size_t destLen = MAX_BUFFER_SIZE;

    uncompress_z(dest, &destLen, Data, Size);
}

static void fuzz_inflateSetDictionary(const uint8_t *Data, size_t Size) {
    z_stream stream;
    memset(&stream, 0, sizeof(stream));
    inflateInit(&stream);

    inflateSetDictionary(&stream, Data, Size);

    inflateEnd(&stream);
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    fuzz_uncompress2_z(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_uncompress(Data, Size);
    fuzz_compress(Data, Size);
    fuzz_uncompress_z(Data, Size);
    fuzz_inflateSetDictionary(Data, Size);

    return 0;
}