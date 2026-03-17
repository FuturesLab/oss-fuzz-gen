#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assuming a temporary directory can be NULL or a valid path if needed
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
}

static void destroy_dummy_iso_file(GF_ISOFile* isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for indices

    GF_ISOFile* isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u32 sampleDescriptionIndex = Data[1];
    u16 bitDepth = 0;

    // Fuzz gf_isom_get_visual_bit_depth
    gf_isom_get_visual_bit_depth(isom_file, trackNumber, sampleDescriptionIndex, &bitDepth);

    u32 colour_type = 0;
    u16 colour_primaries = 0;
    u16 transfer_characteristics = 0;
    u16 matrix_coefficients = 0;
    Bool full_range_flag = 0;

    // Fuzz gf_isom_get_color_info
    gf_isom_get_color_info(isom_file, trackNumber, sampleDescriptionIndex, &colour_type, &colour_primaries, &transfer_characteristics, &matrix_coefficients, &full_range_flag);

    u8 *icc_data = NULL;
    u32 icc_size = 0;

    // Fuzz gf_isom_set_visual_color_info
    gf_isom_set_visual_color_info(isom_file, trackNumber, sampleDescriptionIndex, colour_type, colour_primaries, transfer_characteristics, matrix_coefficients, full_range_flag, icc_data, icc_size);

    u16 revision = 0;
    u32 vendor = 0;
    u32 temporalQ = 0;
    u32 spatialQ = 0;
    u32 horiz_res = 0;
    u32 vert_res = 0;
    u16 frames_per_sample = 0;
    const char *compressor_name = "dummy";
    s16 color_table_index = -1;

    // Fuzz gf_isom_update_video_sample_entry_fields
    gf_isom_update_video_sample_entry_fields(isom_file, trackNumber, sampleDescriptionIndex, revision, vendor, temporalQ, spatialQ, horiz_res, vert_res, frames_per_sample, compressor_name, color_table_index);

    u32 hSpacing = 0;
    u32 vSpacing = 0;

    // Fuzz gf_isom_get_pixel_aspect_ratio
    gf_isom_get_pixel_aspect_ratio(isom_file, trackNumber, sampleDescriptionIndex, &hSpacing, &vSpacing);

    // Fuzz gf_isom_set_visual_bit_depth
    gf_isom_set_visual_bit_depth(isom_file, trackNumber, sampleDescriptionIndex, bitDepth);

    destroy_dummy_iso_file(isom_file);

    return 0;
}