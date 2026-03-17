#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

#define DUMMY_FILE "./dummy_file"

static GF_ISOFile* initialize_iso_file() {
    GF_ISOFile *file = gf_isom_open(DUMMY_FILE, GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 17) return 0;

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    // Prepare dummy file
    FILE *dummy_fp = fopen(DUMMY_FILE, "wb");
    if (!dummy_fp) {
        cleanup_iso_file(isom_file);
        return 0;
    }
    fwrite(Data, 1, Size, dummy_fp);
    fclose(dummy_fp);

    u32 trackNumber = *(u32 *)(Data);
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 sampleNumber = *(u32 *)(Data + 8);
    u32 isLeading = *(u32 *)(Data + 12);
    u32 dependsOn = *(u32 *)(Data + 16);
    u32 dependedOn = *(u32 *)(Data + 20);
    u32 redundant = *(u32 *)(Data + 24);
    u32 new_timescale = *(u32 *)(Data + 28);
    u32 new_tsinc = *(u32 *)(Data + 32);
    u32 force_rescale_type = *(u32 *)(Data + 36);
    u32 TrackID = *(u32 *)(Data + 40);
    u32 Code = *(u32 *)(Data + 44);
    u32 param = *(u32 *)(Data + 48);
    u32 orig_dur = *(u32 *)(Data + 52);
    u32 elapsed_dur = *(u32 *)(Data + 56);
    u32 referenceType = *(u32 *)(Data + 60);
    u32 ReferencedTrackID = *(u32 *)(Data + 64);

    // Call the target functions
    gf_isom_lhvc_force_inband_config(isom_file, trackNumber, sampleDescriptionIndex);
    gf_isom_set_sample_flags(isom_file, trackNumber, sampleNumber, isLeading, dependsOn, dependedOn, redundant);
    gf_isom_set_media_timescale(isom_file, trackNumber, new_timescale, new_tsinc, force_rescale_type);
    gf_isom_set_fragment_option(isom_file, TrackID, Code, param);
    gf_isom_set_fragment_original_duration(isom_file, TrackID, orig_dur, elapsed_dur);
    gf_isom_set_track_reference(isom_file, trackNumber, referenceType, ReferencedTrackID);

    cleanup_iso_file(isom_file);
    return 0;
}