#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + sizeof(s32) * 9) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    s32 matrix[9];
    for (int i = 0; i < 9; i++) {
        matrix[i] = *(s32 *)(Data + sizeof(u32) + sizeof(s32) * i);
    }

    // Fuzz gf_isom_set_track_matrix
    gf_isom_set_track_matrix(isom_file, trackNumber, matrix);

    if (Size < sizeof(u32) * 15) {
        gf_isom_close(isom_file);
        return 0;
    }

    u32 width = *(u32 *)(Data + sizeof(u32) * 10);
    u32 height = *(u32 *)(Data + sizeof(u32) * 11);
    s32 translation_x = *(s32 *)(Data + sizeof(u32) * 12);
    s32 translation_y = *(s32 *)(Data + sizeof(u32) * 13);
    s16 layer = *(s16 *)(Data + sizeof(u32) * 14);

    // Fuzz gf_isom_set_track_layout_info
    gf_isom_set_track_layout_info(isom_file, trackNumber, width, height, translation_x, translation_y, layer);

    // Fuzz gf_isom_set_ipod_compatible
    gf_isom_set_ipod_compatible(isom_file, trackNumber);

    u32 out_width, out_height;
    s32 out_translation_x, out_translation_y;
    s16 out_layer;

    // Fuzz gf_isom_get_track_layout_info
    gf_isom_get_track_layout_info(isom_file, trackNumber, &out_width, &out_height, &out_translation_x, &out_translation_y, &out_layer);

    if (Size < sizeof(u32) * 24 + sizeof(s32) * 2) {
        gf_isom_close(isom_file);
        return 0;
    }

    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32) * 15);
    u32 cleanApertureWidthN = *(u32 *)(Data + sizeof(u32) * 16);
    u32 cleanApertureWidthD = *(u32 *)(Data + sizeof(u32) * 17);
    u32 cleanApertureHeightN = *(u32 *)(Data + sizeof(u32) * 18);
    u32 cleanApertureHeightD = *(u32 *)(Data + sizeof(u32) * 19);
    s32 horizOffN = *(s32 *)(Data + sizeof(u32) * 20);
    u32 horizOffD = *(u32 *)(Data + sizeof(u32) * 21);
    s32 vertOffN = *(s32 *)(Data + sizeof(u32) * 22);
    u32 vertOffD = *(u32 *)(Data + sizeof(u32) * 23);

    // Fuzz gf_isom_set_clean_aperture
    gf_isom_set_clean_aperture(isom_file, trackNumber, sampleDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);

    // Fuzz gf_isom_remove_edits
    gf_isom_remove_edits(isom_file, trackNumber);

    gf_isom_close(isom_file);
    return 0;
}