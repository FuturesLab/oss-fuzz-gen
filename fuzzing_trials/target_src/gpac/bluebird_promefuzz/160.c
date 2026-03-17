#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assuming GF_ISOFile is properly allocated and initialized through some API
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_160(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Ensure there's enough data for basic parameters

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 referenceType = *(u32 *)(Data + 4);
    u32 referenceIndex = *(u32 *)(Data + 8);
    GF_ISOTrackID refTrackID;
    gf_isom_get_reference_ID(isom_file, trackNumber, referenceType, referenceIndex, &refTrackID);

    u32 GroupID = *(u32 *)(Data + 12);
    gf_isom_set_track_interleaving_group(isom_file, trackNumber, GroupID);

    GF_ISOFile *dest_file = create_dummy_iso_file();
    if (!dest_file) {
        cleanup_iso_file(isom_file);
        return 0;
    }
    u32 orig_track = *(u32 *)(Data + 4);
    GF_ISOTrackCloneFlags flags = *(GF_ISOTrackCloneFlags *)(Data + 8);
    u32 dest_track;
    gf_isom_clone_track(isom_file, orig_track, dest_file, flags, &dest_track);

    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 Width, Height;
    gf_isom_get_visual_info(isom_file, trackNumber, sampleDescriptionIndex, &Width, &Height);

    u32 HintDescriptionIndex = *(u32 *)(Data + 4);
    u32 TimeScale = *(u32 *)(Data + 8);
    gf_isom_rtp_set_timescale(isom_file, trackNumber, HintDescriptionIndex, TimeScale);

    u32 sample_number = *(u32 *)(Data + 4);
    u32 grouping_type = *(u32 *)(Data + 8);
    u32 grouping_type_parameter = *(u32 *)(Data + 12);
    u32 sampleGroupDescIndex;
    gf_isom_get_sample_to_group_info(isom_file, trackNumber, sample_number, grouping_type, grouping_type_parameter, &sampleGroupDescIndex);

    cleanup_iso_file(isom_file);
    cleanup_iso_file(dest_file);

    return 0;
}