// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32 at crc32.c:945:15 in zlib.h
// adler32 at adler32.c:128:15 in zlib.h
// crc32_z at crc32.c:625:15 in zlib.h
// adler32_z at adler32.c:61:15 in zlib.h
// crc32_combine64 at crc32.c:975:15 in zlib.h
// crc32_combine_op at crc32.c:968:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <zlib.h>

static uLong safe_crc32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;
    return crc32(0, Data, (uInt)Size);
}

static uLong safe_adler32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;
    return adler32(0, Data, (uInt)Size);
}

static uLong safe_crc32_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;
    return crc32_z(0, Data, (z_size_t)Size);
}

static uLong safe_adler32_z(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;
    return adler32_z(0, Data, (z_size_t)Size);
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz crc32
    uLong crc_result = safe_crc32(Data, Size);

    // Fuzz adler32
    uLong adler_result = safe_adler32(Data, Size);

    // Fuzz crc32_z
    uLong crc_z_result = safe_crc32_z(Data, Size);

    // Fuzz adler32_z
    uLong adler_z_result = safe_adler32_z(Data, Size);

    // Fuzz crc32_combine64
    if (Size >= sizeof(z_off64_t)) {
        z_off64_t len = *(z_off64_t *)Data;
        uLong crc_combined = crc32_combine64(crc_result, crc_z_result, len);
    }

    // Fuzz crc32_combine_op
    if (Size >= sizeof(uLong) * 3) {
        uLong op = *(uLong *)Data;
        uLong crc_combined_op = crc32_combine_op(crc_result, crc_z_result, op);
    }

    return 0;
}