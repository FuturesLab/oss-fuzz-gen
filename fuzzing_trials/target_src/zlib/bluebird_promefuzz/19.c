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

    int level = Data[0] % 10; // Compression level 0-9
    const Bytef *source = (const Bytef *)(Data + 1);
    z_size_t sourceLen = Size - 1;
    z_size_t destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest) {
        compress2_z(dest, &destLen, source, sourceLen, level);
        free(dest);
    }
}

static void fuzz_uncompress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const Bytef *source = (const Bytef *)Data;
    uLong sourceLen = Size;
    uLongf destLen = sourceLen * 4; // Assume a max expansion factor
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest) {
        uncompress2(dest, &destLen, source, &sourceLen);
        free(dest);
    }
}

static void fuzz_uncompress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const Bytef *source = (const Bytef *)Data;
    uLong sourceLen = Size;
    uLongf destLen = sourceLen * 4; // Assume a max expansion factor
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest) {
        uncompress(dest, &destLen, source, sourceLen);
        free(dest);
    }
}

static void fuzz_compress2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    int level = Data[0] % 10; // Compression level 0-9
    const Bytef *source = (const Bytef *)(Data + 1);
    uLong sourceLen = Size - 1;
    uLongf destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest) {
        compress2(dest, &destLen, source, sourceLen, level);
        free(dest);
    }
}

static void fuzz_compress(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const Bytef *source = (const Bytef *)Data;
    uLong sourceLen = Size;
    uLongf destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest) {
        compress(dest, &destLen, source, sourceLen);
        free(dest);
    }
}

static void fuzz_zlibCompileFlags() {
    zlibCompileFlags();
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_uncompress(Data, Size);
    fuzz_compress2(Data, Size);
    fuzz_compress(Data, Size);
    fuzz_zlibCompileFlags();
    return 0;
}