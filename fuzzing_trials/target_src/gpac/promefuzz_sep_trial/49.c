// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_apple_enum_tag_ex at isom_read.c:4491:8 in isomedia.h
// gf_isom_guess_specification at isom_read.c:4276:5 in isomedia.h
// gf_isom_apple_get_tag at isom_read.c:4448:8 in isomedia.h
// gf_isom_apple_set_tag at isom_write.c:6583:8 in isomedia.h
// gf_isom_apple_enum_tag at isom_read.c:4654:8 in isomedia.h
// gf_isom_apple_set_tag_ex at isom_write.c:6298:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 idx = 0;

    GF_ISOiTunesTag out_tag;
    const u8 *data;
    u32 data_len;
    u64 out_int_val;
    u32 out_int_val2;
    u32 out_flags;
    const char *out_mean;
    const char *out_name;
    u32 out_locale;

    // Fuzz gf_isom_apple_enum_tag_ex
    gf_isom_apple_enum_tag_ex(isom_file, idx, &out_tag, &data, &data_len, &out_int_val, &out_int_val2, &out_flags, &out_mean, &out_name, &out_locale);

    // Fuzz gf_isom_guess_specification
    gf_isom_guess_specification(isom_file);

    // Fuzz gf_isom_apple_get_tag
    gf_isom_apple_get_tag(isom_file, out_tag, &data, &data_len);

    // Fuzz gf_isom_apple_set_tag
    gf_isom_apple_set_tag(isom_file, out_tag, data, data_len, out_int_val, out_int_val2);

    // Fuzz gf_isom_apple_enum_tag
    gf_isom_apple_enum_tag(isom_file, idx, &out_tag, &data, &data_len, &out_int_val, &out_int_val2, &out_flags);

    // Fuzz gf_isom_apple_set_tag_ex
    gf_isom_apple_set_tag_ex(isom_file, out_tag, data, data_len, out_int_val, out_int_val2, out_name, out_mean, out_locale);

    // Write dummy file for any file-based operation
    write_dummy_file(Data, Size);

    gf_isom_close(isom_file);
    return 0;
}