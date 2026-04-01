// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_is_adobe_protection_media at drm_sample.c:1901:6 in isomedia.h
// gf_isom_get_sample_sync at isom_read.c:2080:6 in isomedia.h
// gf_isom_get_sample_group_info at isom_read.c:5374:6 in isomedia.h
// gf_isom_is_self_contained at isom_read.c:2158:6 in isomedia.h
// gf_isom_add_sample_group_info at isom_write.c:7555:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    // Ensure there is enough data for track number and indices
    if (Size < 3 * sizeof(u32)) {
        return 0;
    }

    // Write the input data to a dummy file
    write_dummy_file(Data, Size);

    // Create a dummy GF_ISOFile object
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    // Extract track number and indices from input
    u32 trackNumber = *((u32 *)(Data));
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 sampleNumber = *((u32 *)(Data + 2 * sizeof(u32)));

    // Fuzz gf_isom_is_ismacryp_media
    gf_isom_is_ismacryp_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_is_adobe_protection_media
    gf_isom_is_adobe_protection_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_get_sample_sync
    gf_isom_get_sample_sync(isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_get_sample_group_info
    u32 grouping_type = *((u32 *)(Data + 3 * sizeof(u32)));
    u32 default_index = 0;
    const u8 *data = NULL;
    u32 size = 0;
    gf_isom_get_sample_group_info(isom_file, trackNumber, sampleDescriptionIndex, grouping_type, &default_index, &data, &size);

    // Fuzz gf_isom_is_self_contained
    gf_isom_is_self_contained(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_add_sample_group_info
    GF_Err err;
    u32 sampleGroupDescriptionIndex = 0;
    err = gf_isom_add_sample_group_info(isom_file, trackNumber, grouping_type, (void *)Data, Size, GF_FALSE, &sampleGroupDescriptionIndex);

    // Clean up
    gf_isom_close(isom_file);
    return 0;
}