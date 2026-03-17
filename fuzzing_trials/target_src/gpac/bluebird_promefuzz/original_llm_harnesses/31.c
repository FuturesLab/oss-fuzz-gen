// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_sidx_duration at isom_read.c:6196:8 in isomedia.h
// gf_isom_set_edit at isom_write.c:2783:8 in isomedia.h
// gf_isom_force_track_duration at isom_write.c:896:8 in isomedia.h
// gf_isom_set_edit_with_rate at isom_write.c:2789:8 in isomedia.h
// gf_isom_get_edit at isom_read.c:2560:8 in isomedia.h
// gf_isom_patch_last_sample_duration at isom_write.c:1425:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Assuming a maximum size for the GF_ISOFile structure
#define MAX_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(MAX_ISOFILE_SIZE);
    if (!isom_file) return NULL;
    memset(isom_file, 0, MAX_ISOFILE_SIZE);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    // Fuzz gf_isom_get_sidx_duration
    u64 sidx_dur = 0;
    u32 sidx_timescale = 0;
    gf_isom_get_sidx_duration(isom_file, &sidx_dur, &sidx_timescale);

    // Fuzz gf_isom_set_edit
    u32 trackNumber = Data[0];
    u64 EditTime = (Size > 8) ? *((u64 *)(Data + 1)) : 0;
    u64 EditDuration = (Size > 16) ? *((u64 *)(Data + 9)) : 0;
    u64 MediaTime = (Size > 24) ? *((u64 *)(Data + 17)) : 0;
    GF_ISOEditType EditMode = (Size > 32) ? *((GF_ISOEditType *)(Data + 25)) : 0;
    gf_isom_set_edit(isom_file, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    // Fuzz gf_isom_force_track_duration
    u64 duration = (Size > 40) ? *((u64 *)(Data + 33)) : 0;
    gf_isom_force_track_duration(isom_file, trackNumber, duration);

    // Fuzz gf_isom_set_edit_with_rate
    u32 MediaRate = (Size > 48) ? *((u32 *)(Data + 41)) : 0x10000; // Default to normal playback
    gf_isom_set_edit_with_rate(isom_file, trackNumber, EditTime, EditDuration, MediaTime, MediaRate);

    // Fuzz gf_isom_get_edit
    u32 EditIndex = (Size > 52) ? *((u32 *)(Data + 49)) : 1;
    u64 EditTimeOut, SegmentDuration, MediaTimeOut;
    GF_ISOEditType EditModeOut;
    gf_isom_get_edit(isom_file, trackNumber, EditIndex, &EditTimeOut, &SegmentDuration, &MediaTimeOut, &EditModeOut);

    // Fuzz gf_isom_patch_last_sample_duration
    u64 next_dts = (Size > 60) ? *((u64 *)(Data + 53)) : 0;
    gf_isom_patch_last_sample_duration(isom_file, trackNumber, next_dts);

    cleanup_iso_file(isom_file);
    return 0;
}