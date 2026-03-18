// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32_combine at crc32.c:980:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
// adler32_combine64 at adler32.c:162:15 in zlib.h
// crc32_combine_gen at crc32.c:963:15 in zlib.h
// crc32_combine64 at crc32.c:975:15 in zlib.h
// crc32_combine_gen64 at crc32.c:953:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <zlib.h>

static void test_crc32_combine(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off_t)) return;

    uLong crc1 = *(const uLong *)Data;
    uLong crc2 = *(const uLong *)(Data + sizeof(uLong));
    z_off_t len2 = *(const z_off_t *)(Data + sizeof(uLong) * 2);

    if (len2 < 0) len2 = 0; // Ensure len2 is non-negative

    crc32_combine(crc1, crc2, len2);
}

static void test_adler32_combine(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off_t)) return;

    uLong adler1 = *(const uLong *)Data;
    uLong adler2 = *(const uLong *)(Data + sizeof(uLong));
    z_off_t len2 = *(const z_off_t *)(Data + sizeof(uLong) * 2);

    if (len2 < 0) len2 = 0; // Ensure len2 is non-negative

    adler32_combine(adler1, adler2, len2);
}

static void test_adler32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off64_t)) return;

    uLong adler1 = *(const uLong *)Data;
    uLong adler2 = *(const uLong *)(Data + sizeof(uLong));
    z_off64_t len2 = *(const z_off64_t *)(Data + sizeof(uLong) * 2);

    if (len2 < 0) len2 = 0; // Ensure len2 is non-negative

    adler32_combine64(adler1, adler2, len2);
}

static void test_crc32_combine_gen(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off_t)) return;

    z_off_t len2 = *(const z_off_t *)Data;

    if (len2 < 0) len2 = 0; // Ensure len2 is non-negative

    crc32_combine_gen(len2);
}

static void test_crc32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off64_t)) return;

    uLong crc1 = *(const uLong *)Data;
    uLong crc2 = *(const uLong *)(Data + sizeof(uLong));
    z_off64_t len2 = *(const z_off64_t *)(Data + sizeof(uLong) * 2);

    if (len2 < 0) len2 = 0; // Ensure len2 is non-negative

    crc32_combine64(crc1, crc2, len2);
}

static void test_crc32_combine_gen64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off64_t)) return;

    z_off64_t len2 = *(const z_off64_t *)Data;

    if (len2 < 0) len2 = 0; // Ensure len2 is non-negative

    crc32_combine_gen64(len2);
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    test_crc32_combine(Data, Size);
    test_adler32_combine(Data, Size);
    test_adler32_combine64(Data, Size);
    test_crc32_combine_gen(Data, Size);
    test_crc32_combine64(Data, Size);
    test_crc32_combine_gen64(Data, Size);
    return 0;
}