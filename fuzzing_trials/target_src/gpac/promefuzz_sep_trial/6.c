// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_update_aperture_info at isom_write.c:2179:8 in isomedia.h
// gf_isom_fragment_set_sample_av1_switch_frame_group at isom_write.c:7745:8 in isomedia.h
// gf_isom_finalize_for_fragment at movie_fragments.c:85:8 in isomedia.h
// gf_isom_set_sample_rap_group at isom_write.c:7715:8 in isomedia.h
// gf_isom_set_track_group at isom_write.c:8456:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_track_cenc_add_sample_info at drm_sample.c:1309:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return;
    fwrite(Data, 1, Size, file);
    fclose(file);
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 8 + sizeof(Bool) * 7) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    u32 offset = 0;

    u32 trackNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    Bool remove = *(Bool *)(Data + offset);
    offset += sizeof(Bool);

    // Fuzz gf_isom_update_aperture_info
    gf_isom_update_aperture_info(isom_file, trackNumber, remove);

    u32 trackID = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    u32 sample_number_in_frag = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    Bool is_switch_Frame = *(Bool *)(Data + offset);
    offset += sizeof(Bool);

    // Fuzz gf_isom_fragment_set_sample_av1_switch_frame_group
    gf_isom_fragment_set_sample_av1_switch_frame_group(isom_file, trackID, sample_number_in_frag, is_switch_Frame);

    u32 media_segment_type = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    Bool mvex_after_tracks = *(Bool *)(Data + offset);
    offset += sizeof(Bool);

    // Fuzz gf_isom_finalize_for_fragment
    gf_isom_finalize_for_fragment(isom_file, media_segment_type, mvex_after_tracks);

    u32 sampleNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    Bool is_rap = *(Bool *)(Data + offset);
    offset += sizeof(Bool);
    u32 num_leading_samples = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    // Fuzz gf_isom_set_sample_rap_group
    gf_isom_set_sample_rap_group(isom_file, trackNumber, sampleNumber, is_rap, num_leading_samples);

    u32 track_group_id = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    u32 group_type = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    Bool do_add = *(Bool *)(Data + offset);
    offset += sizeof(Bool);

    // Fuzz gf_isom_set_track_group
    gf_isom_set_track_group(isom_file, trackNumber, track_group_id, group_type, do_add);

    u32 container_type = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    Bool use_subsamples = *(Bool *)(Data + offset);
    offset += sizeof(Bool);

    // Ensure we do not read beyond the buffer
    if (offset + sizeof(Bool) * 2 > Size) {
        gf_isom_close(isom_file);
        return 0;
    }

    Bool use_saio_32bit = *(Bool *)(Data + offset);
    offset += sizeof(Bool);
    Bool is_multi_key = *(Bool *)(Data + offset);
    offset += sizeof(Bool);

    u8 *buf = NULL;
    u32 len = 0;
    if (offset < Size) {
        buf = (u8 *)(Data + offset);
        len = (u32)(Size - offset);
    }

    // Fuzz gf_isom_track_cenc_add_sample_info
    gf_isom_track_cenc_add_sample_info(isom_file, trackNumber, container_type, buf, len, use_subsamples, use_saio_32bit, is_multi_key);

    gf_isom_close(isom_file);
    return 0;
}