// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32_combine64 at crc32.c:975:15 in zlib.h
// adler32_combine64 at adler32.c:162:15 in zlib.h
// crc32_combine_gen64 at crc32.c:953:15 in zlib.h
// crc32_combine at crc32.c:980:15 in zlib.h
// crc32_combine_gen at crc32.c:963:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "zlib.h"

static void fuzz_crc32_combine64(uLong crc1, uLong crc2, z_off64_t len2) {
    uLong result = crc32_combine64(crc1, crc2, len2);
    (void)result;  // Suppress unused variable warning
}

static void fuzz_adler32_combine64(uLong adler1, uLong adler2, z_off64_t len2) {
    uLong result = adler32_combine64(adler1, adler2, len2);
    (void)result;  // Suppress unused variable warning
}

static void fuzz_crc32_combine_gen64(z_off64_t len2) {
    uLong result = crc32_combine_gen64(len2);
    (void)result;  // Suppress unused variable warning
}

static void fuzz_crc32_combine(uLong crc1, uLong crc2, z_off_t len2) {
    uLong result = crc32_combine(crc1, crc2, len2);
    (void)result;  // Suppress unused variable warning
}

static void fuzz_crc32_combine_gen(z_off_t len2) {
    uLong result = crc32_combine_gen(len2);
    (void)result;  // Suppress unused variable warning
}

static void fuzz_adler32_combine(uLong adler1, uLong adler2, z_off_t len2) {
    uLong result = adler32_combine(adler1, adler2, len2);
    (void)result;  // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off64_t)) {
        return 0; // Not enough data
    }

    uLong crc1 = *(const uLong *)Data;
    uLong crc2 = *(const uLong *)(Data + sizeof(uLong));
    z_off64_t len2 = *(const z_off64_t *)(Data + sizeof(uLong) * 2);

    fuzz_crc32_combine64(crc1, crc2, len2);
    fuzz_adler32_combine64(crc1, crc2, len2);
    fuzz_crc32_combine_gen64(len2);

    if (Size < sizeof(uLong) * 2 + sizeof(z_off_t)) {
        return 0; // Not enough data for 32-bit functions
    }

    z_off_t len2_32 = *(const z_off_t *)(Data + sizeof(uLong) * 2);
    fuzz_crc32_combine(crc1, crc2, len2_32);
    fuzz_crc32_combine_gen(len2_32);
    fuzz_adler32_combine(crc1, crc2, len2_32);

    return 0;
}