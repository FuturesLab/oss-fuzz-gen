// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_apple_enum_tag_ex at isom_read.c:4491:8 in isomedia.h
// gf_isom_guess_specification at isom_read.c:4276:5 in isomedia.h
// gf_isom_apple_get_tag at isom_read.c:4448:8 in isomedia.h
// gf_isom_apple_set_tag at isom_write.c:6583:8 in isomedia.h
// gf_isom_apple_enum_tag at isom_read.c:4654:8 in isomedia.h
// gf_isom_apple_set_tag_ex at isom_write.c:6298:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include "isomedia.h"

static GF_ISOFile* open_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void close_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = open_iso_file(Data, Size);
    if (!isom_file) return 0;

    // Fuzz gf_isom_apple_enum_tag_ex
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
    gf_isom_apple_enum_tag_ex(isom_file, idx, &out_tag, &data, &data_len, &out_int_val, &out_int_val2, &out_flags, &out_mean, &out_name, &out_locale);

    // Fuzz gf_isom_guess_specification
    u32 brand = gf_isom_guess_specification(isom_file);

    // Fuzz gf_isom_apple_get_tag
    GF_ISOiTunesTag tag = 0;
    const u8 *tag_data;
    u32 tag_data_len;
    gf_isom_apple_get_tag(isom_file, tag, &tag_data, &tag_data_len);

    // Fuzz gf_isom_apple_set_tag
    u64 int_val = 0;
    u32 int_val2 = 0;
    gf_isom_apple_set_tag(isom_file, tag, Data, Size, int_val, int_val2);

    // Fuzz gf_isom_apple_enum_tag
    gf_isom_apple_enum_tag(isom_file, idx, &out_tag, &data, &data_len, &out_int_val, &out_int_val2, &out_flags);

    // Fuzz gf_isom_apple_set_tag_ex
    const char *name = NULL;
    const char *mean = NULL;
    u32 locale = 0;
    gf_isom_apple_set_tag_ex(isom_file, tag, Data, Size, int_val, int_val2, name, mean, locale);

    close_iso_file(isom_file);
    return 0;
}