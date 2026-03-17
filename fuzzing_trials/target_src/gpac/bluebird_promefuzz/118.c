#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for a dummy GF_ISOFile structure
    return (GF_ISOFile*)calloc(1, 1024); // Assuming a size of 1024 bytes for demonstration
}

static void cleanup_iso_file(GF_ISOFile* file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile* isoFile = create_dummy_iso_file();
    if (!isoFile) return 0;

    u32 trackNumber = *((u32*)Data);
    u32 hintDescriptionIndex = *((u32*)(Data + sizeof(u32)));
    u32 timeOffset = *((u32*)(Data + sizeof(u32) * 2));
    u32 refType = trackNumber; // Using trackNumber as refType for simplicity
    u32 sampleNumber = hintDescriptionIndex; // Using hintDescriptionIndex as sampleNumber for simplicity

    // Fuzz gf_isom_sdp_clean_track
    gf_isom_sdp_clean_track(isoFile, trackNumber);

    // Fuzz gf_isom_rtp_set_time_offset
    gf_isom_rtp_set_time_offset(isoFile, trackNumber, hintDescriptionIndex, timeOffset);

    // Fuzz gf_isom_remove_track_reference
    gf_isom_remove_track_reference(isoFile, trackNumber, refType);

    // Fuzz gf_isom_purge_track_reference
    gf_isom_purge_track_reference(isoFile, trackNumber);

    // Fuzz gf_isom_remove_sample
    gf_isom_remove_sample(isoFile, trackNumber, sampleNumber);

    // Prepare dummy HDR info
    GF_MasteringDisplayColourVolumeInfo *mdcv = NULL;
    GF_ContentLightLevelInfo *clli = NULL;

    // Fuzz gf_isom_set_high_dynamic_range_info
    gf_isom_set_high_dynamic_range_info(isoFile, trackNumber, hintDescriptionIndex, mdcv, clli);

    cleanup_iso_file(isoFile);
    return 0;
}