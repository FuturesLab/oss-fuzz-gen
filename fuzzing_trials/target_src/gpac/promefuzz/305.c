// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_is_self_contained at isom_read.c:2158:6 in isomedia.h
// gf_isom_get_sample_sync at isom_read.c:2080:6 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_is_adobe_protection_media at drm_sample.c:1901:6 in isomedia.h
// gf_isom_get_sample_group_info at isom_read.c:5374:6 in isomedia.h
// gf_isom_is_track_encrypted at isom_read.c:1624:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
    remove(DUMMY_FILE_PATH);
}

int LLVMFuzzerTestOneInput_305(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u32 sampleDescriptionIndex = *((u32*)(Data + sizeof(u32)));
    u32 sampleNumber = *((u32*)(Data + sizeof(u32) * 2));

    // Fuzz gf_isom_is_self_contained
    gf_isom_is_self_contained(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_get_sample_sync
    gf_isom_get_sample_sync(isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_is_ismacryp_media
    gf_isom_is_ismacryp_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_is_adobe_protection_media
    gf_isom_is_adobe_protection_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_get_sample_group_info
    u32 default_index;
    const u8 *data;
    u32 size;
    gf_isom_get_sample_group_info(isom_file, trackNumber, sampleDescriptionIndex, 0, &default_index, &data, &size);

    // Fuzz gf_isom_is_track_encrypted
    gf_isom_is_track_encrypted(isom_file, trackNumber);

    cleanup_iso_file(isom_file);
    return 0;
}