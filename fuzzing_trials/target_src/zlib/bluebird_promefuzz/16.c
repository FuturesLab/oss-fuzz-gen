#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

static void fuzz_compress2_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Need at least 1 byte to determine compression level

    int level = Data[0] % 10; // Compression level range: 0-9
    const Bytef *source = Data + 1;
    z_size_t sourceLen = Size - 1;

    uLong destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress2_z(dest, &destLen, source, sourceLen, level);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

static void fuzz_compress_z(const uint8_t *Data, size_t Size) {
    const Bytef *source = Data;
    z_size_t sourceLen = Size;

    uLong destLen = compressBound(sourceLen);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return;

    int result = compress_z(dest, &destLen, source, sourceLen);
    if (result != Z_OK) {
        // Handle error if needed
    }

    free(dest);
}

static void fuzz_compressBound(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong)) return;

    uLong sourceLen;
    memcpy(&sourceLen, Data, sizeof(uLong));

    uLong bound = compressBound(sourceLen);
    // Use `bound` if needed
}

static void fuzz_deflateBound_z(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_size_t)) return;

    z_streamp strm = (z_streamp)malloc(sizeof(z_stream));
    if (!strm) return;

    memset(strm, 0, sizeof(z_stream));
    z_size_t sourceLen;
    memcpy(&sourceLen, Data, sizeof(z_size_t));

    z_size_t bound = deflateBound_z(strm, sourceLen);
    // Use `bound` if needed

    free(strm);
}

static void fuzz_deflateBound(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong)) return;

    z_streamp strm = (z_streamp)malloc(sizeof(z_stream));
    if (!strm) return;

    memset(strm, 0, sizeof(z_stream));
    uLong sourceLen;
    memcpy(&sourceLen, Data, sizeof(uLong));

    uLong bound = deflateBound(strm, sourceLen);
    // Use `bound` if needed

    free(strm);
}

static void fuzz_compressBound_z(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_size_t)) return;

    z_size_t sourceLen;
    memcpy(&sourceLen, Data, sizeof(z_size_t));

    z_size_t bound = compressBound_z(sourceLen);
    // Use `bound` if needed
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_compress_z(Data, Size);
    fuzz_compressBound(Data, Size);
    fuzz_deflateBound_z(Data, Size);
    fuzz_deflateBound(Data, Size);
    fuzz_compressBound_z(Data, Size);
    return 0;
}