// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_freeze_order at isom_read.c:76:8 in isomedia.h
// gf_isom_set_byte_offset at isom_read.c:5910:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_set_sample_group_in_traf at isom_write.c:8537:8 in isomedia.h
// gf_isom_remove_root_od at isom_write.c:165:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* open_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return file;
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    // Write fuzz data to a dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    GF_ISOFile *file = open_iso_file();
    if (!file) return 0;

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(file);

    // Fuzz gf_isom_set_byte_offset with a random offset
    if (Size >= sizeof(s64)) {
        s64 byte_offset = *(s64 *)Data;
        gf_isom_set_byte_offset(file, byte_offset);
    }

    // Fuzz gf_isom_enable_mfra
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