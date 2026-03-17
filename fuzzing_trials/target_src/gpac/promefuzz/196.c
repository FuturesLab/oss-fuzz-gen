// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_sidx_duration at isom_read.c:6196:8 in isomedia.h
// gf_isom_get_file_offset_for_time at isom_read.c:6170:8 in isomedia.h
// gf_isom_set_fragment_reference_time at movie_fragments.c:2552:8 in isomedia.h
// gf_isom_get_creation_time at isom_read.c:994:8 in isomedia.h
// gf_isom_reset_data_offset at isom_read.c:3151:8 in isomedia.h
// gf_isom_get_edit at isom_read.c:2560:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Define a dummy structure size for GF_ISOFile since the actual structure is incomplete
#define DUMMY_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_isofile() {
    // Allocate a dummy structure for GF_ISOFile
    GF_ISOFile *file = (GF_ISOFile *)malloc(DUMMY_ISOFILE_SIZE);
    if (!file) return NULL;
    memset(file, 0, DUMMY_ISOFILE_SIZE);
    return file;
}

static void cleanup_isofile(GF_ISOFile *file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_196(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    u64 sidx_dur, offset, creationTime, modificationTime, EditTime, SegmentDuration, MediaTime;
    u32 sidx_timescale, trackNumber, EditIndex;
    GF_ISOEditType EditMode;
    GF_Err err;

    // Fuzz gf_isom_get_sidx_duration
    err = gf_isom_get_sidx_duration(isom_file, &sidx_dur, &sidx_timescale);

    // Fuzz gf_isom_get_file_offset_for_time
    if (Size >= sizeof(Double)) {
        Double start_time;
        memcpy(&start_time, Data, sizeof(Double));
        err = gf_isom_get_file_offset_for_time(isom_file, start_time, &offset);
    }

    // Fuzz gf_isom_set_fragment_reference_time
    if (Size >= sizeof(GF_ISOTrackID) + 2 * sizeof(u64) + sizeof(Bool)) {
        GF_ISOTrackID reference_track_ID;
        u64 ntp, timestamp;
        Bool at_mux;
        memcpy(&reference_track_ID, Data, sizeof(GF_ISOTrackID));
        memcpy(&ntp, Data + sizeof(GF_ISOTrackID), sizeof(u64));
        memcpy(&timestamp, Data + sizeof(GF_ISOTrackID) + sizeof(u64), sizeof(u64));
        memcpy(&at_mux, Data + sizeof(GF_ISOTrackID) + 2 * sizeof(u64), sizeof(Bool));
        err = gf_isom_set_fragment_reference_time(isom_file, reference_track_ID, ntp, timestamp, at_mux);
    }

    // Fuzz gf_isom_get_creation_time
    err = gf_isom_get_creation_time(isom_file, &creationTime, &modificationTime);

    // Fuzz gf_isom_reset_data_offset
    err = gf_isom_reset_data_offset(isom_file, &offset);

    // Fuzz gf_isom_get_edit
    if (Size >= 2 * sizeof(u32)) {
        memcpy(&trackNumber, Data, sizeof(u32));
        memcpy(&EditIndex, Data + sizeof(u32), sizeof(u32));
        err = gf_isom_get_edit(isom_file, trackNumber, EditIndex, &EditTime, &SegmentDuration, &MediaTime, &EditMode);
    }

    cleanup_isofile(isom_file);
    return 0;
}