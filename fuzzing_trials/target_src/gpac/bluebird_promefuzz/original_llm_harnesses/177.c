// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_is_video_handler_type at isom_read.c:5954:6 in isomedia.h
// gf_isom_get_tmcd_config at sample_descs.c:1953:8 in isomedia.h
// gf_isom_has_meta_xml at meta.c:52:5 in isomedia.h
// gf_isom_get_tile_info at isom_read.c:5878:6 in isomedia.h
// gf_isom_get_edit_list_type at isom_read.c:2504:6 in isomedia.h
// gf_isom_is_external_track at isom_read.c:6656:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Define a dummy size for the incomplete type
#define DUMMY_ISOFILE_SIZE 1024

static void initialize_dummy_iso_file(GF_ISOFile **isom_file) {
    *isom_file = (GF_ISOFile *)malloc(DUMMY_ISOFILE_SIZE);
    if (*isom_file) {
        memset(*isom_file, 0, DUMMY_ISOFILE_SIZE);
    }
}

static void cleanup_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_177(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Test gf_isom_is_video_handler_type
    u32 mtype = *((u32 *)Data);
    gf_isom_is_video_handler_type(mtype);

    // Prepare to test gf_isom_get_tmcd_config
    GF_ISOFile *isom_file = NULL;
    initialize_dummy_iso_file(&isom_file);
    if (!isom_file) return 0;

    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    u32 tmcd_flags, tmcd_fps_num, tmcd_fps_den, tmcd_fpt;
    gf_isom_get_tmcd_config(isom_file, trackNumber, sampleDescriptionIndex, &tmcd_flags, &tmcd_fps_num, &tmcd_fps_den, &tmcd_fpt);

    // Test gf_isom_has_meta_xml
    Bool root_meta = GF_TRUE;
    u32 track_num = 0;
    gf_isom_has_meta_xml(isom_file, root_meta, track_num);

    // Test gf_isom_get_tile_info
    u32 sample_group_description_index = 1;
    u32 default_sample_group_index, id, independent, x, y, w, h;
    Bool full_frame;
    gf_isom_get_tile_info(isom_file, trackNumber, sample_group_description_index, &default_sample_group_index, &id, &independent, &full_frame, &x, &y, &w, &h);

    // Test gf_isom_get_edit_list_type
    s64 mediaOffset;
    gf_isom_get_edit_list_type(isom_file, trackNumber, &mediaOffset);

    // Test gf_isom_is_external_track
    GF_ISOTrackID tkid;
    u32 type, flags;
    const char *location;
    gf_isom_is_external_track(isom_file, trackNumber, &tkid, &type, &flags, &location);

    // Cleanup
    cleanup_dummy_iso_file(isom_file);
    return 0;
}