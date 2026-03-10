// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32_combine_op at crc32.c:968:15 in zlib.h
// adler32 at adler32.c:128:15 in zlib.h
// adler32 at adler32.c:128:15 in zlib.h
// adler32_z at adler32.c:61:15 in zlib.h
// adler32_z at adler32.c:61:15 in zlib.h
// crc32_combine64 at crc32.c:975:15 in zlib.h
// crc32_z at crc32.c:625:15 in zlib.h
// crc32_z at crc32.c:625:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <zlib.h>

static void fuzz_crc32(const uint8_t *Data, size_t Size) {
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, Data, (uInt)Size);
}

static void fuzz_crc32_combine_op(const uint8_t *Data, size_t Size) {
    if (Size < 8) return;
    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + 4);
    uLong op = crc32_combine_op(crc1, crc2, 0);
}

static void fuzz_adler32(const uint8_t *Data, size_t Size) {
    uLong adler = adler32(0L, Z_NULL, 0);
    adler = adler32(adler, Data, (uInt)Size);
}

static void fuzz_adler32_z(const uint8_t *Data, size_t Size) {
    uLong adler = adler32_z(0L, Z_NULL, 0);
    adler = adler32_z(adler, Data, (z_size_t)Size);
}

static void fuzz_crc32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < 16) return;
    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + 8);
    z_off64_t len2 = (z_off64_t)(Size - 16);
    uLong combined = crc32_combine64(crc1, crc2, len2);
}

static void fuzz_crc32_z(const uint8_t *Data, size_t Size) {
    uLong crc = crc32_z(0L, Z_NULL, 0);
    crc = crc32_z(crc, Data, (z_size_t)Size);
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    fuzz_crc32(Data, Size);
    fuzz_crc32_combine_op(Data, Size);
    fuzz_adler32(Data, Size);
    fuzz_adler32_z(Data, Size);
    fuzz_crc32_combine64(Data, Size);
    fuzz_crc32_z(Data, Size);
    return 0;
}