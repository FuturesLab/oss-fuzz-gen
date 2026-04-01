// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// adler32 at adler32.c:128:15 in zlib.h
// adler32_z at adler32.c:61:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
// adler32_combine64 at adler32.c:162:15 in zlib.h
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

static void test_adler32(const uint8_t *Data, size_t Size) {
    uLong adler = 0;
    adler = adler32(adler, Data, (uInt)Size);
}

static void test_adler32_z(const uint8_t *Data, size_t Size) {
    uLong adler = 0;
    adler = adler32_z(adler, Data, (z_size_t)Size);
}

static void test_adler32_combine(const uint8_t *Data, size_t Size) {
    if (Size < 8) return;
    uLong adler1 = *(uLong*)Data;
    uLong adler2 = *(uLong*)(Data + 4);
    z_off_t len2 = (z_off_t)(Size - 8);
    adler32_combine(adler1, adler2, len2);
}

static void test_adler32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < 16) return;
    uLong adler1 = *(uLong*)Data;
    uLong adler2 = *(uLong*)(Data + 8);
    z_off64_t len2 = (z_off64_t)(Size - 16);
    adler32_combine64(adler1, adler2, len2);
}

static void test_crc32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < 16) return;
    uLong crc1 = *(uLong*)Data;
    uLong crc2 = *(uLong*)(Data + 8);
    z_off64_t len2 = (z_off64_t)(Size - 16);
    crc32_combine64(crc1, crc2, len2);
}

static void test_crc32_combine_gen64(const uint8_t *Data, size_t Size) {
    if (Size < 8) return;
    z_off64_t len = (z_off64_t)(Size - 8);
    crc32_combine_gen64(len);
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    test_adler32(Data, Size);
    test_adler32_z(Data, Size);
    test_adler32_combine(Data, Size);
    test_adler32_combine64(Data, Size);
    test_crc32_combine64(Data, Size);
    test_crc32_combine_gen64(Data, Size);
    return 0;
}