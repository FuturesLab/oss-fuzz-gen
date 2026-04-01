// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_reset_tables at isom_read.c:3407:8 in isomedia.h
// gf_isom_apply_box_patch at isom_write.c:8665:8 in isomedia.h
// gf_isom_release_segment at isom_read.c:3459:8 in isomedia.h
// gf_isom_flush_fragments at movie_fragments.c:1468:8 in isomedia.h
// gf_isom_fragment_set_sample_rap_group at isom_write.c:7720:8 in isomedia.h
// gf_isom_clone_pssh at isom_write.c:8420:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for GF_ISOFile using a generic pointer
    GF_ISOFile *iso_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void destroy_dummy_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_300(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Fuzz gf_isom_reset_tables
    Bool reset_sample_count = Data[0] % 2;
    gf_isom_reset_tables(iso_file, reset_sample_count);

    // Fuzz gf_isom_apply_box_patch
    const char *box_patch_filename = "./dummy_file";
    FILE *dummy_file = fopen(box_patch_filename, "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }
    GF_ISOTrackID trackID = (Size > 1) ? Data[1] : 0;
    Bool for_fragments = (Size > 2) ? Data[2] % 2 : 0;
    gf_isom_apply_box_patch(iso_file, trackID, box_patch_filename, for_fragments);

    // Fuzz gf_isom_release_segment
    Bool reset_tables = (Size > 3) ? Data[3] % 2 : 0;
    gf_isom_release_segment(iso_file, reset_tables);

    // Fuzz gf_isom_flush_fragments
    Bool last_segment = (Size > 4) ? Data[4] % 2 : 0;
    gf_isom_flush_fragments(iso_file, last_segment);

    // Fuzz gf_isom_fragment_set_sample_rap_group
    u32 sample_number_in_frag = (Size > 5) ? Data[5] : 0;
    Bool is_rap = (Size > 6) ? Data[6] % 2 : 0;
    u32 num_leading_samples = (Size > 7) ? Data[7] : 0;
    gf_isom_fragment_set_sample_rap_group(iso_file, trackID, sample_number_in_frag, is_rap, num_leading_samples);

    // Fuzz gf_isom_clone_pssh
    GF_ISOFile *src_file = create_dummy_iso_file();
    if (src_file) {
        Bool in_moof = (Size > 8) ? Data[8] % 2 : 0;
        gf_isom_clone_pssh(iso_file, src_file, in_moof);
        destroy_dummy_iso_file(src_file);
    }

    destroy_dummy_iso_file(iso_file);
    remove(box_patch_filename);

    return 0;
}