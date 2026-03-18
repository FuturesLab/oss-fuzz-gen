// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_segment_get_track_fragment_count at isom_read.c:895:5 in isomedia.h
// gf_isom_get_next_alternate_group_id at isom_read.c:4851:5 in isomedia.h
// gf_isom_vp_config_get at avc_ext.c:2626:14 in isomedia.h
// gf_isom_get_next_moof_number at movie_fragments.c:3482:5 in isomedia.h
// gf_isom_get_sample_description_count at isom_read.c:1373:5 in isomedia.h
// gf_isom_get_udta_count at isom_read.c:2692:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy GF_ISOFile object
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    // Use the data to influence the behavior of the fuzzing
    u32 moof_index = (Size > 0) ? Data[0] : 1;
    u32 trackNumber = (Size > 1) ? Data[1] : 1;
    u32 sampleDescriptionIndex = (Size > 2) ? Data[2] : 1;

    // Call the target API functions
    u32 track_fragment_count = gf_isom_segment_get_track_fragment_count(isom_file, moof_index);
    u32 next_alternate_group_id = gf_isom_get_next_alternate_group_id(isom_file);
    GF_VPConfig *vp_config = gf_isom_vp_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    u32 next_moof_number = gf_isom_get_next_moof_number(isom_file);
    u32 sample_description_count = gf_isom_get_sample_description_count(isom_file, trackNumber);
    u32 udta_count = gf_isom_get_udta_count(isom_file, trackNumber);

    // Free the VPConfig if allocated
    if (vp_config) {
        free(vp_config);
    }

    // Clean up
    gf_isom_close(isom_file);

    return 0;
}