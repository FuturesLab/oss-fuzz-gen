// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_sdp_clean_track at hint_track.c:790:8 in isomedia.h
// gf_isom_set_last_sample_duration at isom_write.c:1419:8 in isomedia.h
// gf_isom_remove_track_reference at isom_write.c:5051:8 in isomedia.h
// gf_isom_allocate_sidx at movie_fragments.c:1347:8 in isomedia.h
// gf_isom_set_pixel_aspect_ratio at isom_write.c:1847:8 in isomedia.h
// gf_isom_rtp_packet_set_offset at hint_track.c:653:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!isom_file) {
        return 0;
    }

    // Prepare additional parameters
    u32 trackNumber = (Size > 0) ? Data[0] : 0;
    u32 duration = (Size > 1) ? Data[1] : 0;
    u32 ref_type = (Size > 2) ? Data[2] : 0;
    u32 nb_segs = (Size > 3) ? Data[3] : 0;
    u32 sampleDescriptionIndex = (Size > 4) ? Data[4] : 0;
    s32 hSpacing = (Size > 5) ? Data[5] : 0;
    s32 vSpacing = (Size > 6) ? Data[6] : 0;
    Bool force_par = (Size > 7) ? Data[7] : 0;
    s32 timeOffset = (Size > 8) ? Data[8] : 0;

    // Dummy variables for gf_isom_allocate_sidx
    u32 *frags_per_segment = NULL;
    u32 *start_range = NULL;
    u32 *end_range = NULL;
    s32 subsegs_per_sidx = 0;
    Bool daisy_chain_sidx = 0;
    Bool use_ssix = 0;

    // Call the target functions
    gf_isom_sdp_clean_track(isom_file, trackNumber);
    gf_isom_set_last_sample_duration(isom_file, trackNumber, duration);
    gf_isom_remove_track_reference(isom_file, trackNumber, ref_type);
    gf_isom_allocate_sidx(isom_file, subsegs_per_sidx, daisy_chain_sidx, nb_segs, frags_per_segment, start_range, end_range, use_ssix);
    gf_isom_set_pixel_aspect_ratio(isom_file, trackNumber, sampleDescriptionIndex, hSpacing, vSpacing, force_par);
    gf_isom_rtp_packet_set_offset(isom_file, trackNumber, timeOffset);

    // Clean up
    gf_isom_close(isom_file);

    return 0;
}