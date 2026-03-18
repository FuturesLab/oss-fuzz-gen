// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_add_subsample at isom_write.c:7028:8 in isomedia.h
// gf_isom_set_track_group at isom_write.c:8456:8 in isomedia.h
// gf_isom_set_track_enabled at isom_write.c:256:8 in isomedia.h
// gf_isom_set_track_switch_parameter at isom_write.c:6872:8 in isomedia.h
// gf_isom_set_composition_offset_mode at isom_write.c:8001:8 in isomedia.h
// gf_isom_get_sample_rap_roll_info at isom_read.c:5119:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_278(const uint8_t *Data, size_t Size) {
    if (Size < 49) { // Ensure there's enough data for all operations
        return 0;
    }

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32*)Data;
    u32 sampleNumber = *(u32*)(Data + 4);
    u32 flags = *(u32*)(Data + 8);
    u32 subSampleSize = *(u32*)(Data + 12);
    u8 priority = *(u8*)(Data + 16);
    u32 reserved = *(u32*)(Data + 17);
    Bool discardable = *(Bool*)(Data + 21);

    gf_isom_add_subsample(isom_file, trackNumber, sampleNumber, flags, subSampleSize, priority, reserved, discardable);

    u32 track_group_id = *(u32*)(Data + 22);
    u32 group_type = *(u32*)(Data + 26);
    Bool do_add = *(Bool*)(Data + 30);

    gf_isom_set_track_group(isom_file, trackNumber, track_group_id, group_type, do_add);

    Bool enableTrack = *(Bool*)(Data + 31);

    gf_isom_set_track_enabled(isom_file, trackNumber, enableTrack);

    u32 trackRefGroup = *(u32*)(Data + 32);
    Bool is_switch_group = *(Bool*)(Data + 36);
    u32 switchGroupID = *(u32*)(Data + 37);
    u32 criteriaList[1] = {*(u32*)(Data + 41)};
    u32 criteriaListCount = 1;

    gf_isom_set_track_switch_parameter(isom_file, trackNumber, trackRefGroup, is_switch_group, &switchGroupID, criteriaList, criteriaListCount);

    Bool use_negative_offsets = *(Bool*)(Data + 45);

    gf_isom_set_composition_offset_mode(isom_file, trackNumber, use_negative_offsets);

    Bool is_rap;
    GF_ISOSampleRollType roll_type;
    s32 roll_distance;

    gf_isom_get_sample_rap_roll_info(isom_file, trackNumber, sampleNumber, &is_rap, &roll_type, &roll_distance);

    cleanup_iso_file(isom_file);
    return 0;
}