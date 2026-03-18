// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
// gf_isom_get_pl_indication at isom_read.c:4079:4 in isomedia.h
// gf_isom_get_mode at isom_read.c:53:4 in isomedia.h
// gf_isom_set_next_moof_number at movie_fragments.c:3474:6 in isomedia.h
// gf_isom_reset_sample_count at isom_read.c:5005:6 in isomedia.h
// gf_isom_enable_traf_map_templates at isom_read.c:6026:6 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file pointer
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void destroy_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_delete(isom_file);
    }
}

int LLVMFuzzerTestOneInput_259(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    uint8_t pl_code = Data[0];

    // Fuzz gf_isom_get_pl_indication
    u8 pl_indication = gf_isom_get_pl_indication(isom_file, (GF_ISOProfileLevelType)pl_code);

    // Fuzz gf_isom_get_mode
    u8 mode = gf_isom_get_mode(isom_file);

    // Fuzz gf_isom_set_next_moof_number
    if (Size >= 5) {
        u32 moof_number = *(u32 *)(Data + 1);
        gf_isom_set_next_moof_number(isom_file, moof_number);
    }

    // Fuzz gf_isom_reset_sample_count
    gf_isom_reset_sample_count(isom_file);

    // Fuzz gf_isom_enable_traf_map_templates
    gf_isom_enable_traf_map_templates(isom_file);

    // Cleanup
    destroy_dummy_iso_file(isom_file);

    return 0;
}