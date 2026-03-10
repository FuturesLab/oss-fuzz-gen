#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "zlib.h"

static void fuzz_crc32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off64_t)) return;
    uLong crc1 = *(const uLong*)Data;
    uLong crc2 = *(const uLong*)(Data + sizeof(uLong));
    z_off64_t len2 = *(const z_off64_t*)(Data + 2 * sizeof(uLong));
    crc32_combine64(crc1, crc2, len2);
}

static void fuzz_crc32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong)) return;
    uLong crc = *(const uLong*)Data;
    const Bytef *buf = Data + sizeof(uLong);
    uInt len = (uInt)(Size - sizeof(uLong));
    crc32(crc, buf, len);
}

static void fuzz_crc32_combine_gen64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off64_t)) return;
    z_off64_t len = *(const z_off64_t*)Data;
    crc32_combine_gen64(len);
}

static void fuzz_crc32_combine_op(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 3) return;
    uLong crc1 = *(const uLong*)Data;
    uLong crc2 = *(const uLong*)(Data + sizeof(uLong));
    uLong op = *(const uLong*)(Data + 2 * sizeof(uLong));
    crc32_combine_op(crc1, crc2, op);
}

static void fuzz_get_crc_table(void) {
    get_crc_table();
}

static void fuzz_crc32_z(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong)) return;
    uLong crc = *(const uLong*)Data;
    const Bytef *buf = Data + sizeof(uLong);
    z_size_t len = (z_size_t)(Size - sizeof(uLong));
    crc32_z(crc, buf, len);
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    fuzz_crc32_combine64(Data, Size);
    fuzz_crc32(Data, Size);
    fuzz_crc32_combine_gen64(Data, Size);
    fuzz_crc32_combine_op(Data, Size);
    fuzz_get_crc_table();
    fuzz_crc32_z(Data, Size);
    return 0;
}