// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:92:15 in zlib.h
// compress2_z at compress.c:24:13 in zlib.h
// uncompress2 at uncompr.c:79:13 in zlib.h
// uncompress at uncompr.c:93:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress2 at compress.c:63:13 in zlib.h
// compressBound at compress.c:92:15 in zlib.h
// compress at compress.c:78:13 in zlib.h
// zlibCompileFlags at zutil.c:31:15 in zlib.h
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
#include <zlib.h>

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

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    fuzz_compress2_z(Data, Size);
    fuzz_uncompress2(Data, Size);
    fuzz_uncompress(Data, Size);
    fuzz_compress2(Data, Size);
    fuzz_compress(Data, Size);
    fuzz_zlibCompileFlags();
    return 0;
}