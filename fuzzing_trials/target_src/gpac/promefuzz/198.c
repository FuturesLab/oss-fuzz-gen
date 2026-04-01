// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_is_cenc_media at drm_sample.c:681:6 in isomedia.h
// gf_isom_is_self_contained at isom_read.c:2158:6 in isomedia.h
// gf_isom_is_adobe_protection_media at drm_sample.c:1901:6 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_is_omadrm_media at drm_sample.c:237:6 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_198(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(u32)) {
        return 0;
    }

    write_dummy_iso_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));

    // Test gf_isom_is_cenc_media
    Bool is_cenc = gf_isom_is_cenc_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Test gf_isom_is_self_contained
    Bool is_self_contained = gf_isom_is_self_contained(isom_file, trackNumber, sampleDescriptionIndex);

    // Test gf_isom_is_adobe_protection_media
    Bool is_adobe_protected = gf_isom_is_adobe_protection_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Test gf_isom_is_ismacryp_media
    Bool is_ismacryp = gf_isom_is_ismacryp_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Test gf_isom_is_omadrm_media
    Bool is_omadrm = gf_isom_is_omadrm_media(isom_file, trackNumber, sampleDescriptionIndex);

    gf_isom_close(isom_file);
    return 0;
}