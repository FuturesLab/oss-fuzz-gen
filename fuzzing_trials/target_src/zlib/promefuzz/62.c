// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// get_crc_table at crc32.c:481:29 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32_z at crc32.c:625:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32_combine64 at crc32.c:975:15 in zlib.h
// crc32_combine_gen at crc32.c:963:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32_combine_op at crc32.c:968:15 in zlib.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzzing get_crc_table
    const z_crc_t *crc_table = get_crc_table();
    if (crc_table == NULL) return 0;

    // Fuzzing crc32
    uLong initial_crc = 0;
    uLong crc_result = crc32(initial_crc, Data, (uInt)Size);

    // Fuzzing crc32_z
    uLong crc_z_result = crc32_z(initial_crc, Data, (z_size_t)Size);

    // Fuzzing crc32_combine64
    if (Size >= 8) {
        uLong crc1 = crc32(0, Data, (uInt)(Size / 2));
        uLong crc2 = crc32(0, Data + (Size / 2), (uInt)(Size - (Size / 2)));
        uLong combined_crc64 = crc32_combine64(crc1, crc2, (z_off64_t)(Size - (Size / 2)));
    }

    // Fuzzing crc32_combine_gen and crc32_combine_op
    if (Size >= 4) {
        z_off_t len2 = (z_off_t)Size;
        uLong op = crc32_combine_gen(len2);
        uLong crc1 = crc32(0, Data, (uInt)(Size / 2));
        uLong crc2 = crc32(0, Data + (Size / 2), (uInt)(Size - (Size / 2)));
        uLong combined_crc_op = crc32_combine_op(crc1, crc2, op);
    }

    // Write data to a dummy file if needed by any function
    write_dummy_file(Data, Size);

    return 0;
}