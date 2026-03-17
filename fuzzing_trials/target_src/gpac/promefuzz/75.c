// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_has_meta_xml at meta.c:52:5 in isomedia.h
// gf_isom_is_external_track at isom_read.c:6656:6 in isomedia.h
// gf_isom_get_edit_list_type at isom_read.c:2504:6 in isomedia.h
// gf_isom_get_tile_info at isom_read.c:5878:6 in isomedia.h
// gf_isom_get_tmcd_config at sample_descs.c:1953:8 in isomedia.h
// gf_isom_is_video_handler_type at isom_read.c:5954:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *iso_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    // Write the input data to a dummy file
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Create a dummy ISO file
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) {
        remove(DUMMY_FILE_PATH);
        return 0;
    }

    // Prepare variables for function calls
    Bool root_meta = (Bool)(Data[0] % 2);
    u32 track_num = *(u32 *)(Data + 1) % 100; // Limit track number to a reasonable range
    u32 tkid, type, flags;
    const char *location;
    s64 mediaOffset;
    u32 default_sample_group_index, id, independent, x, y, w, h;
    u32 tmcd_flags, tmcd_fps_num, tmcd_fps_den, tmcd_fpt;

    // Call gf_isom_has_meta_xml
    u32 has_meta_xml = gf_isom_has_meta_xml(iso_file, root_meta, track_num);

    // Call gf_isom_is_external_track
    Bool is_external = gf_isom_is_external_track(iso_file, track_num, &tkid, &type, &flags, &location);

    // Call gf_isom_get_edit_list_type
    Bool edit_list_type = gf_isom_get_edit_list_type(iso_file, track_num, &mediaOffset);

    // Call gf_isom_get_tile_info
    Bool tile_info = gf_isom_get_tile_info(iso_file, track_num, track_num, &default_sample_group_index, &id, &independent, &root_meta, &x, &y, &w, &h);

    // Call gf_isom_get_tmcd_config
    GF_Err tmcd_config_err = gf_isom_get_tmcd_config(iso_file, track_num, track_num, &tmcd_flags, &tmcd_fps_num, &tmcd_fps_den, &tmcd_fpt);

    // Call gf_isom_is_video_handler_type
    Bool is_video_handler = gf_isom_is_video_handler_type(*(u32 *)Data);

    // Cleanup
    cleanup_iso_file(iso_file);
    remove(DUMMY_FILE_PATH);

    return 0;
}