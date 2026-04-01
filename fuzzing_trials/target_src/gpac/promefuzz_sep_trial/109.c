// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_sample_references at isom_write.c:9510:8 in isomedia.h
// gf_isom_set_clean_aperture at isom_write.c:2132:8 in isomedia.h
// gf_isom_get_track_layout_info at isom_read.c:4116:8 in isomedia.h
// gf_isom_get_clean_aperture at isom_read.c:6405:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_get_sample_flags at isom_read.c:1913:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
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

static GF_ISOFile *create_dummy_isofile() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    u32 trackNumber = 1;
    u32 sampleNumber = 1;
    s32 ID = 1;
    u32 nb_refs = 0;
    s32 *refs = NULL;

    if (Size > sizeof(u32) * 5) {
        refs = (s32 *)(Data + sizeof(u32) * 5);
        nb_refs = (Size - sizeof(u32) * 5) / sizeof(s32);
    }

    // Fuzz gf_isom_set_sample_references
    gf_isom_set_sample_references(isom_file, trackNumber, sampleNumber, ID, nb_refs, refs);

    // Fuzz gf_isom_set_clean_aperture
    u32 sampleDescriptionIndex = 1;
    u32 cleanApertureWidthN = 1920;
    u32 cleanApertureWidthD = 1;
    u32 cleanApertureHeightN = 1080;
    u32 cleanApertureHeightD = 1;
    s32 horizOffN = 0;
    u32 horizOffD = 1;
    s32 vertOffN = 0;
    u32 vertOffD = 1;

    gf_isom_set_clean_aperture(isom_file, trackNumber, sampleDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);

    // Fuzz gf_isom_get_track_layout_info
    u32 width, height;
    s32 translation_x, translation_y;
    s16 layer;
    gf_isom_get_track_layout_info(isom_file, trackNumber, &width, &height, &translation_x, &translation_y, &layer);

    // Fuzz gf_isom_get_clean_aperture
    u32 cleanApertureWidthN_out, cleanApertureWidthD_out;
    u32 cleanApertureHeightN_out, cleanApertureHeightD_out;
    s32 horizOffN_out, vertOffN_out;
    u32 horizOffD_out, vertOffD_out;

    gf_isom_get_clean_aperture(isom_file, trackNumber, sampleDescriptionIndex, &cleanApertureWidthN_out, &cleanApertureWidthD_out, &cleanApertureHeightN_out, &cleanApertureHeightD_out, &horizOffN_out, &horizOffD_out, &vertOffN_out, &vertOffD_out);

    // Fuzz gf_isom_set_track_id
    GF_ISOTrackID new_trackID = 2;
    gf_isom_set_track_id(isom_file, trackNumber, new_trackID);

    // Fuzz gf_isom_get_sample_flags
    u32 is_leading, dependsOn, dependedOn, redundant;
    gf_isom_get_sample_flags(isom_file, trackNumber, sampleNumber, &is_leading, &dependsOn, &dependedOn, &redundant);

    gf_isom_close(isom_file);
    return 0;
}