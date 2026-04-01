// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:92:15 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress_z at compress.c:73:13 in zlib.h
// deflateBound_z at deflate.c:857:18 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

static void fuzz_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    z_size_t sourceLen = Size;
    const Bytef *source = (const Bytef *)Data;
    z_size_t destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int level = Data[0] % 10; // Compression level between 0 to 9

    int result = compress2_z(dest, &destLen, source, sourceLen, level);
    if (result != Z_OK) {
        fprintf(stderr, "compress2_z failed: %d\n", result);
    }

    free(dest);
}

static void fuzz_compress_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    z_size_t sourceLen = Size;
    const Bytef *source = (const Bytef *)Data;
    z_size_t destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress_z(dest, &destLen, source, sourceLen);
    if (result != Z_OK) {
        fprintf(stderr, "compress_z failed: %d\n", result);
    }

    free(dest);
}

static void fuzz_deflateBound_z(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_stream)) return;

    z_stream strm;
    memcpy(&strm, Data, sizeof(z_stream));
    z_size_t sourceLen = Size - sizeof(z_stream);

    z_size_t bound = deflateBound_z(&strm, sourceLen);
    if (bound == (z_size_t)-1) {
        fprintf(stderr, "deflateBound_z failed\n");
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_compress_z(Data, Size);
    fuzz_deflateBound_z(Data, Size);

    return 0;
}