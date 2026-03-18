// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_sample_references at isom_write.c:9510:8 in isomedia.h
// gf_isom_get_chapter_count at isom_read.c:1526:5 in isomedia.h
// gf_isom_set_clean_aperture at isom_write.c:2132:8 in isomedia.h
// gf_isom_get_composition_offset_shift at isom_read.c:5507:5 in isomedia.h
// gf_isom_get_track_layout_info at isom_read.c:4116:8 in isomedia.h
// gf_isom_get_track_original_id at isom_read.c:824:15 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_258(const uint8_t *Data, size_t Size) {
    // Prepare the environment for testing
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!iso_file) return 0;

    u32 trackNumber = 0;
    if (Size >= sizeof(u32)) {
        trackNumber = *((u32 *)Data);
        Data += sizeof(u32);
        Size -= sizeof(u32);
    }

    // Test gf_isom_set_sample_references
    if (Size >= sizeof(u32) + sizeof(s32) + sizeof(u32)) {
        u32 sampleNumber = *((u32 *)Data);
        Data += sizeof(u32);
        s32 ID = *((s32 *)Data);
        Data += sizeof(s32);
        u32 nb_refs = *((u32 *)Data);
        Data += sizeof(u32);

        s32 *refs = NULL;
        if (Size >= nb_refs * sizeof(s32)) {
            refs = (s32 *)Data;
            Data += nb_refs * sizeof(s32);
        }

        gf_isom_set_sample_references(iso_file, trackNumber, sampleNumber, ID, nb_refs, refs);
    }

    // Test gf_isom_get_chapter_count
    u32 chapter_count = gf_isom_get_chapter_count(iso_file, trackNumber);

    // Test gf_isom_set_clean_aperture
    if (Size >= 6 * sizeof(u32) + 2 * sizeof(s32)) {
        u32 sampleDescriptionIndex = *((u32 *)Data);
        Data += sizeof(u32);
        u32 cleanApertureWidthN = *((u32 *)Data);
        Data += sizeof(u32);
        u32 cleanApertureWidthD = *((u32 *)Data);
        Data += sizeof(u32);
        u32 cleanApertureHeightN = *((u32 *)Data);
        Data += sizeof(u32);
        u32 cleanApertureHeightD = *((u32 *)Data);
        Data += sizeof(u32);
        s32 horizOffN = *((s32 *)Data);
        Data += sizeof(s32);
        u32 horizOffD = *((u32 *)Data);
        Data += sizeof(u32);
        s32 vertOffN = *((s32 *)Data);
        Data += sizeof(s32);
        u32 vertOffD = *((u32 *)Data);
        Data += sizeof(u32);

        gf_isom_set_clean_aperture(iso_file, trackNumber, sampleDescriptionIndex, cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD, horizOffN, horizOffD, vertOffN, vertOffD);
    }

    // Test gf_isom_get_composition_offset_shift
    s32 composition_offset_shift = gf_isom_get_composition_offset_shift(iso_file, trackNumber);

    // Test gf_isom_get_track_layout_info
    u32 width = 0, height = 0;
    s32 translation_x = 0, translation_y = 0;
    s16 layer = 0;
    gf_isom_get_track_layout_info(iso_file, trackNumber, &width, &height, &translation_x, &translation_y, &layer);

    // Test gf_isom_get_track_original_id
    GF_ISOTrackID original_id = gf_isom_get_track_original_id(iso_file, trackNumber);

    // Clean up
    gf_isom_close(iso_file);

    return 0;
}