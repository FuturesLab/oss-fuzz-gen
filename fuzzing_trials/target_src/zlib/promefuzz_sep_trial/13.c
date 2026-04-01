// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32_combine_gen at crc32.c:963:15 in zlib.h
// crc32_combine_op at crc32.c:968:15 in zlib.h
// crc32_combine at crc32.c:980:15 in zlib.h
// crc32_combine64 at crc32.c:975:15 in zlib.h
// crc32_combine_gen64 at crc32.c:953:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

static void fuzz_crc32(const uint8_t *Data, size_t Size) {
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, Data, (uInt)Size);
}

static void fuzz_crc32_combine_gen(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off_t)) return;
    z_off_t len2 = *(z_off_t *)Data;
    crc32_combine_gen(len2);
}

static void fuzz_crc32_combine_op(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(uLong)) return;
    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + sizeof(uLong));
    uLong op = *(uLong *)(Data + 2 * sizeof(uLong));
    crc32_combine_op(crc1, crc2, op);
}

static void fuzz_crc32_combine(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off_t) + 2 * sizeof(uLong)) return;
    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + sizeof(uLong));
    z_off_t len2 = *(z_off_t *)(Data + 2 * sizeof(uLong));
    crc32_combine(crc1, crc2, len2);
}

static void fuzz_crc32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off64_t) + 2 * sizeof(uLong)) return;
    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + sizeof(uLong));
    z_off64_t len2 = *(z_off64_t *)(Data + 2 * sizeof(uLong));
    crc32_combine64(crc1, crc2, len2);
}

static void fuzz_crc32_combine_gen64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off64_t)) return;
    z_off64_t len2 = *(z_off64_t *)Data;
    crc32_combine_gen64(len2);
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    fuzz_crc32(Data, Size);
    fuzz_crc32_combine_gen(Data, Size);
    fuzz_crc32_combine_op(Data, Size);
    fuzz_crc32_combine(Data, Size);
    fuzz_crc32_combine64(Data, Size);
    fuzz_crc32_combine_gen64(Data, Size);
    return 0;
}