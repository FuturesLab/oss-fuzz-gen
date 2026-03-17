// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_keep_utc_times at isom_read.c:5543:6 in isomedia.h
// gf_isom_enable_traf_map_templates at isom_read.c:6026:6 in isomedia.h
// gf_isom_get_mode at isom_read.c:53:4 in isomedia.h
// gf_isom_get_pl_indication at isom_read.c:4079:4 in isomedia.h
// gf_isom_reset_sample_count at isom_read.c:5005:6 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(GF_ISOProfileLevelType) + 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    GF_ISOProfileLevelType PL_Code = *(GF_ISOProfileLevelType *)(Data + 1);
    u8 mode, pl_indication;
    Bool keep_utc = (Bool)(Data[0] % 2);

    // Test gf_isom_keep_utc_times
    gf_isom_keep_utc_times(isom_file, keep_utc);

    // Test gf_isom_enable_traf_map_templates
    gf_isom_enable_traf_map_templates(isom_file);

    // Test gf_isom_get_mode
    mode = gf_isom_get_mode(isom_file);

    // Test gf_isom_get_pl_indication
    pl_indication = gf_isom_get_pl_indication(isom_file, PL_Code);

    // Test gf_isom_reset_sample_count
    gf_isom_reset_sample_count(isom_file);

    // Test gf_isom_delete
    gf_isom_delete(isom_file);

    return 0;
}