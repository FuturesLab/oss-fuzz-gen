#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    // Ensure there is enough data to proceed
    if (Size < sizeof(u32) * 3) {
        return 0;
    }

    // Create a dummy file from input data
    write_dummy_file(Data, Size);

    // Open the dummy file as an ISO file
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = Data[0];
    u32 group_index = Data[1];
    u32 switchGroupID = 0;
    u32 criteriaListSize = 0;

    const u32 *criteriaList = gf_isom_get_track_switch_parameter(isom_file, trackNumber, group_index, &switchGroupID, &criteriaListSize);

    s32 compositionOffsetShift = gf_isom_get_composition_offset_shift(isom_file, trackNumber);

    u32 chapterCount = gf_isom_get_chapter_count(isom_file, trackNumber);

    u32 width = 0, height = 0;
    s32 translation_x = 0, translation_y = 0;
    s16 layer = 0;
    GF_Err layoutErr = gf_isom_get_track_layout_info(isom_file, trackNumber, &width, &height, &translation_x, &translation_y, &layer);

    u32 sampleDescriptionIndex = Data[2];
    u32 cleanApertureWidthN = 1920, cleanApertureWidthD = 1;
    u32 cleanApertureHeightN = 1080, cleanApertureHeightD = 1;
    s32 horizOffN = 0, vertOffN = 0;
    u32 horizOffD = 1, vertOffD = 1;
    GF_Err apertureErr = gf_isom_set_clean_aperture(isom_file, trackNumber, sampleDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);

    u32 sampleNumber = 1;
    s32 ID = 1;
    u32 nb_refs = 0;
    s32 *refs = NULL;
    GF_Err sampleRefErr = gf_isom_set_sample_references(isom_file, trackNumber, sampleNumber, ID, nb_refs, refs);

    gf_isom_close(isom_file);

    return 0;
}