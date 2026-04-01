// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_set_nalu_extract_mode at isom_read.c:5481:8 in isomedia.h
// gf_isom_has_track_reference at isom_read.c:1295:5 in isomedia.h
// gf_isom_get_nalu_extract_mode at isom_read.c:5499:23 in isomedia.h
// gf_isom_get_next_moof_number at movie_fragments.c:3482:5 in isomedia.h
// gf_isom_set_default_sync_track at isom_read.c:4209:6 in isomedia.h
// gf_isom_get_next_alternate_group_id at isom_read.c:4851:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    // Allocate memory for GF_ISOFile using a dummy size
    GF_ISOFile *file = (GF_ISOFile *)malloc(1024); // Assuming a dummy size
    if (!file) return NULL;
    memset(file, 0, 1024);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_240(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    GF_ISOFile *isoFile = initialize_iso_file();
    if (!isoFile) return 0;

    u32 trackNumber = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 naluExtractMode = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 referenceType = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    GF_ISOTrackID refTrackID = *((GF_ISOTrackID *)Data);
    Data += sizeof(GF_ISOTrackID);
    Size -= sizeof(GF_ISOTrackID);

    // Fuzz gf_isom_set_nalu_extract_mode
    gf_isom_set_nalu_extract_mode(isoFile, trackNumber, (GF_ISONaluExtractMode)naluExtractMode);

    // Fuzz gf_isom_has_track_reference
    gf_isom_has_track_reference(isoFile, trackNumber, referenceType, refTrackID);

    // Fuzz gf_isom_get_nalu_extract_mode
    gf_isom_get_nalu_extract_mode(isoFile, trackNumber);

    // Fuzz gf_isom_get_next_moof_number
    gf_isom_get_next_moof_number(isoFile);

    // Fuzz gf_isom_set_default_sync_track
    gf_isom_set_default_sync_track(isoFile, trackNumber);

    // Fuzz gf_isom_get_next_alternate_group_id
    gf_isom_get_next_alternate_group_id(isoFile);

    cleanup_iso_file(isoFile);
    return 0;
}