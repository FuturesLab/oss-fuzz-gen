#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* open_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return file;
}

int LLVMFuzzerTestOneInput_274(const uint8_t *Data, size_t Size) {
    // Write fuzz data to a dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    GF_ISOFile *file = open_iso_file();
    if (!file) {
        return 0;
    }

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(file);

    // Fuzz gf_isom_set_byte_offset with a random offset
    if (Size >= sizeof(s64)) {
        s64 byte_offset = *(s64 *)Data;
        gf_isom_set_byte_offset(file, byte_offset);
    }

    // Fuzz gf_isom_enable_mfra

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_freeze_order to gf_isom_get_copyright
    u32 ret_gf_isom_segment_get_fragment_count_wuvct = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_get_copyright_afhdp = gf_isom_get_copyright(file, ret_gf_isom_segment_get_fragment_count_wuvct, (const char **)Data, (const char **)"w");

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_enable_mfra(file);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(file);

    // Fuzz gf_isom_set_sample_group_in_traf
    gf_isom_set_sample_group_in_traf(file);

    // Fuzz gf_isom_remove_root_od
    gf_isom_remove_root_od(file);

    gf_isom_close(file);
    return 0;
}