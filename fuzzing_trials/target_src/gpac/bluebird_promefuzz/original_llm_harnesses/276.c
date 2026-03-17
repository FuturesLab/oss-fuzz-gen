// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_make_interleave_ex at isom_write.c:6032:8 in isomedia.h
// gf_isom_clone_pl_indications at isom_write.c:3891:8 in isomedia.h
// gf_isom_reset_data_offset at isom_read.c:3151:8 in isomedia.h
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_release_segment at isom_read.c:3459:8 in isomedia.h
// gf_isom_remove_root_od at isom_write.c:165:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assume that GF_ISOFile is properly created using a library function
    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile* iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_276(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(GF_Fraction)) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    GF_Fraction interleave_time;
    memcpy(&interleave_time, Data, sizeof(GF_Fraction));

    // Fuzz gf_isom_make_interleave_ex
    gf_isom_make_interleave_ex(iso_file, &interleave_time);

    // Fuzz gf_isom_clone_pl_indications
    GF_ISOFile* dest_file = create_dummy_iso_file();
    if (dest_file) {
        gf_isom_clone_pl_indications(iso_file, dest_file);
        cleanup_iso_file(dest_file);
    }

    // Fuzz gf_isom_reset_data_offset
    u64 top_box_start = 0;
    gf_isom_reset_data_offset(iso_file, &top_box_start);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(iso_file);

    // Fuzz gf_isom_release_segment
    gf_isom_release_segment(iso_file, 1);

    // Fuzz gf_isom_remove_root_od
    gf_isom_remove_root_od(iso_file);

    cleanup_iso_file(iso_file);
    return 0;
}