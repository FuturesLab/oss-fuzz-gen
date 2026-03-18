// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_sidx_duration at isom_read.c:6196:8 in isomedia.h
// gf_isom_append_edit at isom_write.c:2849:8 in isomedia.h
// gf_isom_force_track_duration at isom_write.c:896:8 in isomedia.h
// gf_isom_patch_last_sample_duration at isom_write.c:1425:8 in isomedia.h
// gf_isom_set_media_timescale at isom_write.c:5276:8 in isomedia.h
// gf_isom_set_traf_base_media_decode_time at movie_fragments.c:3443:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE "./dummy_file"

static GF_ISOFile* create_dummy_iso_file() {
    // As we cannot allocate GF_ISOFile directly, assume a function exists to create it
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE, GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    // Create a dummy file to work with
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u64 sidx_dur;
    u32 sidx_timescale;
    gf_isom_get_sidx_duration(isom_file, &sidx_dur, &sidx_timescale);

    u32 trackNumber = (Size > 4) ? *(u32 *)Data : 1;
    u64 EditDuration = (Size > 12) ? *(u64 *)(Data + 4) : 1000;
    u64 MediaTime = (Size > 20) ? *(u64 *)(Data + 12) : 0;
    GF_ISOEditType EditMode = (Size > 24) ? *(GF_ISOEditType *)(Data + 20) : 0;
    gf_isom_append_edit(isom_file, trackNumber, EditDuration, MediaTime, EditMode);

    u64 duration = (Size > 28) ? *(u64 *)(Data + 24) : 2000;
    gf_isom_force_track_duration(isom_file, trackNumber, duration);

    u64 next_dts = (Size > 36) ? *(u64 *)(Data + 32) : 3000;
    gf_isom_patch_last_sample_duration(isom_file, trackNumber, next_dts);

    u32 new_timescale = (Size > 40) ? *(u32 *)(Data + 36) : 600;
    u32 new_tsinc = (Size > 44) ? *(u32 *)(Data + 40) : 0;
    u32 force_rescale_type = (Size > 48) ? *(u32 *)(Data + 44) : 0;
    gf_isom_set_media_timescale(isom_file, trackNumber, new_timescale, new_tsinc, force_rescale_type);

    GF_ISOTrackID TrackID = (Size > 52) ? *(GF_ISOTrackID *)(Data + 48) : 1;
    u64 decode_time = (Size > 60) ? *(u64 *)(Data + 52) : 4000;
    gf_isom_set_traf_base_media_decode_time(isom_file, TrackID, decode_time);

    cleanup_iso_file(isom_file);
    return 0;
}