// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_min_negative_cts_offset at isom_read.c:6700:5 in isomedia.h
// gf_isom_get_track_switch_parameter at isom_read.c:4831:12 in isomedia.h
// gf_isom_get_composition_offset_shift at isom_read.c:5507:5 in isomedia.h
// gf_isom_get_track_id at isom_read.c:796:15 in isomedia.h
// gf_isom_get_track_layout_info at isom_read.c:4116:8 in isomedia.h
// gf_isom_rtp_packet_set_offset at hint_track.c:653:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Define a dummy size for GF_ISOFile since it's an incomplete type
#define DUMMY_GF_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for GF_ISOFile using a dummy size
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(DUMMY_GF_ISOFILE_SIZE);
    if (!isom_file) return NULL;
    memset(isom_file, 0, DUMMY_GF_ISOFILE_SIZE);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_270(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    Data += sizeof(u32);
    Size -= sizeof(u32);

    // Fuzz gf_isom_get_min_negative_cts_offset
    if (Size >= sizeof(GF_ISOMMinNegCtsQuery)) {
        GF_ISOMMinNegCtsQuery query_mode = *(GF_ISOMMinNegCtsQuery *)Data;
        s32 min_neg_cts_offset = gf_isom_get_min_negative_cts_offset(isom_file, trackNumber, query_mode);
    }

    // Fuzz gf_isom_get_track_switch_parameter
    if (Size >= 2 * sizeof(u32)) {
        u32 group_index = *(u32 *)Data;
        Data += sizeof(u32);
        u32 switchGroupID = 0;
        u32 criteriaListSize = 0;
        const u32 *criteriaList = gf_isom_get_track_switch_parameter(isom_file, trackNumber, group_index, &switchGroupID, &criteriaListSize);
    }

    // Fuzz gf_isom_get_composition_offset_shift
    s32 comp_offset_shift = gf_isom_get_composition_offset_shift(isom_file, trackNumber);

    // Fuzz gf_isom_get_track_id
    GF_ISOTrackID track_id = gf_isom_get_track_id(isom_file, trackNumber);

    // Fuzz gf_isom_get_track_layout_info
    u32 width = 0, height = 0;
    s32 translation_x = 0, translation_y = 0;
    s16 layer = 0;
    GF_Err layout_info_err = gf_isom_get_track_layout_info(isom_file, trackNumber, &width, &height, &translation_x, &translation_y, &layer);

    // Fuzz gf_isom_rtp_packet_set_offset
    if (Size >= sizeof(s32)) {
        s32 timeOffset = *(s32 *)Data;
        GF_Err rtp_offset_err = gf_isom_rtp_packet_set_offset(isom_file, trackNumber, timeOffset);
    }

    cleanup_iso_file(isom_file);
    return 0;
}