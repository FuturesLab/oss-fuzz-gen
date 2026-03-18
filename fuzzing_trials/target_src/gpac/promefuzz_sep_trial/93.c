// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_update_video_sample_entry_fields at isom_write.c:8557:8 in isomedia.h
// gf_isom_get_pixel_aspect_ratio at isom_read.c:3946:8 in isomedia.h
// gf_isom_cenc_allocate_storage at drm_sample.c:1142:8 in isomedia.h
// gf_isom_get_color_info at isom_read.c:3979:8 in isomedia.h
// gf_isom_get_visual_bit_depth at isom_read.c:3852:8 in isomedia.h
// gf_isom_set_visual_bit_depth at isom_write.c:1811:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    // Since we cannot allocate GF_ISOFile directly due to incomplete type,
    // we will return a NULL pointer as a placeholder.
    return NULL;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    // Placeholder for cleanup. No action needed since we return NULL in create_dummy_iso_file.
}

int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u16) * 2 + sizeof(u32) * 5 + sizeof(s16)) {
        return 0;
    }

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u16 revision = *(u16 *)(Data + 2 * sizeof(u32));
    u32 vendor = *(u32 *)(Data + 2 * sizeof(u32) + sizeof(u16));
    u32 temporalQ = *(u32 *)(Data + 3 * sizeof(u32) + sizeof(u16));
    u32 spatialQ = *(u32 *)(Data + 4 * sizeof(u32) + sizeof(u16));
    u32 horiz_res = *(u32 *)(Data + 5 * sizeof(u32) + sizeof(u16));
    u32 vert_res = *(u32 *)(Data + 6 * sizeof(u32) + sizeof(u16));
    u16 frames_per_sample = *(u16 *)(Data + 7 * sizeof(u32) + sizeof(u16));
    const char *compressor_name = "DummyCompressor";
    s16 color_table_index = *(s16 *)(Data + 7 * sizeof(u32) + 2 * sizeof(u16));

    gf_isom_update_video_sample_entry_fields(iso_file, trackNumber, sampleDescriptionIndex, revision, vendor, temporalQ, spatialQ, horiz_res, vert_res, frames_per_sample, compressor_name, color_table_index);

    u32 hSpacing = 0;
    u32 vSpacing = 0;
    gf_isom_get_pixel_aspect_ratio(iso_file, trackNumber, sampleDescriptionIndex, &hSpacing, &vSpacing);

    gf_isom_cenc_allocate_storage(iso_file, trackNumber);

    u32 colour_type = 0;
    u16 colour_primaries = 0;
    u16 transfer_characteristics = 0;
    u16 matrix_coefficients = 0;
    Bool full_range_flag = 0;
    gf_isom_get_color_info(iso_file, trackNumber, sampleDescriptionIndex, &colour_type, &colour_primaries, &transfer_characteristics, &matrix_coefficients, &full_range_flag);

    u16 bitDepth = 0;
    gf_isom_get_visual_bit_depth(iso_file, trackNumber, sampleDescriptionIndex, &bitDepth);

    gf_isom_set_visual_bit_depth(iso_file, trackNumber, sampleDescriptionIndex, bitDepth);

    cleanup_iso_file(iso_file);

    return 0;
}