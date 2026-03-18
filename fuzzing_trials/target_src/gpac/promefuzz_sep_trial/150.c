// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_clean_aperture at isom_write.c:2132:8 in isomedia.h
// gf_isom_get_track_layout_info at isom_read.c:4116:8 in isomedia.h
// gf_isom_set_visual_info at isom_write.c:1769:8 in isomedia.h
// gf_isom_set_track_matrix at isom_write.c:5254:8 in isomedia.h
// gf_isom_set_track_layout_info at isom_write.c:5263:8 in isomedia.h
// gf_isom_check_data_reference at isom_read.c:1705:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 10 + sizeof(s32) * 3 + sizeof(s16)) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)(Data);
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 cleanApertureWidthN = *(u32 *)(Data + 8);
    u32 cleanApertureWidthD = *(u32 *)(Data + 12);
    u32 cleanApertureHeightN = *(u32 *)(Data + 16);
    u32 cleanApertureHeightD = *(u32 *)(Data + 20);
    s32 horizOffN = *(s32 *)(Data + 24);
    u32 horizOffD = *(u32 *)(Data + 28);
    s32 vertOffN = *(s32 *)(Data + 32);
    u32 vertOffD = *(u32 *)(Data + 36);

    gf_isom_set_clean_aperture(isom_file, trackNumber, sampleDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);

    u32 width, height;
    s32 translation_x, translation_y;
    s16 layer;
    gf_isom_get_track_layout_info(isom_file, trackNumber, &width, &height, &translation_x, &translation_y, &layer);

    u32 Width = *(u32 *)(Data + 40);
    u32 Height = *(u32 *)(Data + 44);
    gf_isom_set_visual_info(isom_file, trackNumber, sampleDescriptionIndex, Width, Height);

    s32 matrix[9];
    for (int i = 0; i < 9; i++) {
        matrix[i] = *(s32 *)(Data + 48 + i * 4);
    }
    gf_isom_set_track_matrix(isom_file, trackNumber, matrix);

    s32 translation_x_fp = *(s32 *)(Data + 84);
    s32 translation_y_fp = *(s32 *)(Data + 88);
    s16 layer_fp = *(s16 *)(Data + 92);
    gf_isom_set_track_layout_info(isom_file, trackNumber, width, height, translation_x_fp, translation_y_fp, layer_fp);

    gf_isom_check_data_reference(isom_file, trackNumber, sampleDescriptionIndex);

    gf_isom_close(isom_file);

    return 0;
}