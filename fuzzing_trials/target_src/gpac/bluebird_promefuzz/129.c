#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for the GF_ISOFile structure
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Size > 0 ? Data[0] : 0;
    u32 sampleDescriptionIndex = Size > 1 ? Data[1] : 0;

    u32 tmcd_flags, tmcd_fps_num, tmcd_fps_den, tmcd_fpt;
    gf_isom_get_tmcd_config(iso_file, trackNumber, sampleDescriptionIndex, &tmcd_flags, &tmcd_fps_num, &tmcd_fps_den, &tmcd_fpt);

    u16 rvc_predefined = Size > 2 ? Data[2] : 0;
    char mime[] = "video/mp4";
    gf_isom_set_rvc_config(iso_file, trackNumber, sampleDescriptionIndex, rvc_predefined, mime, (u8 *)Data, Size);

    u16 revision = Size > 3 ? Data[3] : 0;
    u32 vendor = Size > 4 ? Data[4] : 0;
    u32 temporalQ = Size > 5 ? Data[5] : 0;
    u32 spatialQ = Size > 6 ? Data[6] : 0;
    u32 horiz_res = Size > 7 ? Data[7] : 0;
    u32 vert_res = Size > 8 ? Data[8] : 0;
    u16 frames_per_sample = Size > 9 ? Data[9] : 0;
    const char compressor_name[] = "compressor";
    s16 color_table_index = -1;
    gf_isom_update_video_sample_entry_fields(iso_file, trackNumber, sampleDescriptionIndex, revision, vendor, temporalQ, spatialQ, horiz_res, vert_res, frames_per_sample, compressor_name, color_table_index);

    u16 rvc_predefined_out;
    u8 *data_out;
    u32 size_out;
    const char *mime_out;
    gf_isom_get_rvc_config(iso_file, trackNumber, sampleDescriptionIndex, &rvc_predefined_out, &data_out, &size_out, &mime_out);

    u32 average_bitrate = Size > 10 ? Data[10] : 0;
    u32 max_bitrate = Size > 11 ? Data[11] : 0;
    u32 decode_buffer_size = Size > 12 ? Data[12] : 0;
    gf_isom_update_bitrate(iso_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);

    u32 Width, Height;
    gf_isom_get_visual_info(iso_file, trackNumber, sampleDescriptionIndex, &Width, &Height);

    cleanup_iso_file(iso_file);
    return 0;
}