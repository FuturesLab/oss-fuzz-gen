// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_default_sync_track at isom_read.c:4209:6 in isomedia.h
// gf_isom_has_time_offset at isom_read.c:1868:5 in isomedia.h
// gf_isom_get_sample_size at isom_read.c:2007:5 in isomedia.h
// gf_isom_get_track_by_id at isom_read.c:807:5 in isomedia.h
// gf_isom_new_track at isom_write.c:863:5 in isomedia.h
// gf_isom_get_hevc_lhvc_type at avc_ext.c:2728:17 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Allocate a GF_ISOFile assuming a minimal structure size
    GF_ISOFile *isom = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom;
}

static void cleanup_isofile(GF_ISOFile *isom) {
    if (isom) {
        // Close the ISO file and free resources
        gf_isom_close(isom);
    }
}

int LLVMFuzzerTestOneInput_221(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom = create_dummy_isofile();
    if (!isom) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = (Size >= 2 * sizeof(u32)) ? *(u32 *)(Data + sizeof(u32)) : 1;
    u32 trackID = (Size >= 3 * sizeof(u32)) ? *(u32 *)(Data + 2 * sizeof(u32)) : 1;
    u32 MediaType = (Size >= 4 * sizeof(u32)) ? *(u32 *)(Data + 3 * sizeof(u32)) : 0;
    u32 TimeScale = (Size >= 5 * sizeof(u32)) ? *(u32 *)(Data + 4 * sizeof(u32)) : 1;
    u32 sampleDescriptionIndex = (Size >= 6 * sizeof(u32)) ? *(u32 *)(Data + 5 * sizeof(u32)) : 1;

    gf_isom_set_default_sync_track(isom, trackNumber);
    u32 timeOffset = gf_isom_has_time_offset(isom, trackNumber);
    u32 sampleSize = gf_isom_get_sample_size(isom, trackNumber, sampleNumber);
    u32 trackByID = gf_isom_get_track_by_id(isom, trackID);
    u32 newTrack = gf_isom_new_track(isom, trackID, MediaType, TimeScale);
    GF_ISOMHEVCType hevcType = gf_isom_get_hevc_lhvc_type(isom, trackNumber, sampleDescriptionIndex);

    // Use the return values to avoid compiler optimizations
    (void)timeOffset;
    (void)sampleSize;
    (void)trackByID;
    (void)newTrack;
    (void)hevcType;

    cleanup_isofile(isom);
    return 0;
}