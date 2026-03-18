// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_ismacryp_sample_from_data at drm_sample.c:48:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_ismacryp_new_sample at drm_sample.c:31:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_get_ismacryp_sample at drm_sample.c:159:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_set_ismacryp_protection at drm_sample.c:559:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Open a dummy file to simulate an ISO file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fclose(file);

    // Use gpac's API to open the file as an ISO file
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_279(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy ISO file
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Use the first byte as a track number and the second byte as a sample description index
    u32 trackNumber = Data[0];
    u32 sampleDescriptionIndex = (Size > 1) ? Data[1] : 0;

    // 1. Test gf_isom_is_ismacryp_media
    Bool is_ismacryp = gf_isom_is_ismacryp_media(iso_file, trackNumber, sampleDescriptionIndex);

    // 2. Test gf_isom_ismacryp_sample_from_data
    u8 *sample_data = (u8 *)Data;
    u32 dataLength = (u32)Size;
    Bool use_selective_encryption = GF_FALSE;
    u8 KI_length = 0;
    u8 IV_length = 0;
    GF_ISMASample *sample = gf_isom_ismacryp_sample_from_data(sample_data, dataLength, use_selective_encryption, KI_length, IV_length);
    gf_isom_ismacryp_delete_sample(sample);

    // 3. Test gf_isom_ismacryp_new_sample
    GF_ISMASample *new_sample = gf_isom_ismacryp_new_sample();
    gf_isom_ismacryp_delete_sample(new_sample);

    // 4. Test gf_isom_get_ismacryp_sample
    GF_ISOSample iso_sample;
    memset(&iso_sample, 0, sizeof(GF_ISOSample));
    GF_ISMASample *ismacryp_sample = gf_isom_get_ismacryp_sample(iso_file, trackNumber, &iso_sample, sampleDescriptionIndex);
    gf_isom_ismacryp_delete_sample(ismacryp_sample);

    // 5. Test gf_isom_set_ismacryp_protection
    u32 scheme_type = 0;
    u32 scheme_version = 1;
    char *scheme_uri = "scheme_uri";
    char *kms_URI = "kms_URI";
    Bool selective_encryption = GF_FALSE;
    u32 KI_length_protection = 0;
    u32 IV_length_protection = 0;
    GF_Err err = gf_isom_set_ismacryp_protection(iso_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, scheme_uri, kms_URI, selective_encryption, KI_length_protection, IV_length_protection);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}