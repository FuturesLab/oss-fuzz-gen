// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_get_ismacryp_sample at drm_sample.c:159:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_ismacryp_sample_from_data at drm_sample.c:48:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_set_ismacryp_protection at drm_sample.c:559:8 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_ismacryp_new_sample at drm_sample.c:31:16 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static void fuzz_gf_isom_ismacryp_delete_sample() {
    GF_ISMASample *sample = gf_isom_ismacryp_new_sample();
    if (sample) {
        sample->dataLength = 0; // Set to 0 to retain buffer
        gf_isom_ismacryp_delete_sample(sample);
    }
}

static void fuzz_gf_isom_get_ismacryp_sample(GF_ISOFile *isom_file) {
    GF_ISOSample samp;
    memset(&samp, 0, sizeof(GF_ISOSample));
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;

    GF_ISMASample *sample = gf_isom_get_ismacryp_sample(isom_file, trackNumber, &samp, sampleDescriptionIndex);
    if (sample) {
        gf_isom_ismacryp_delete_sample(sample);
    }
}

static void fuzz_gf_isom_ismacryp_sample_from_data(const uint8_t *Data, size_t Size) {
    Bool use_selective_encryption = GF_FALSE;
    u8 KI_length = 0;
    u8 IV_length = 0;

    GF_ISMASample *sample = gf_isom_ismacryp_sample_from_data((u8 *)Data, (u32)Size, use_selective_encryption, KI_length, IV_length);
    if (sample) {
        gf_isom_ismacryp_delete_sample(sample);
    }
}

static void fuzz_gf_isom_set_ismacryp_protection(GF_ISOFile *isom_file) {
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    u32 scheme_type = GF_ISOM_ISMACRYP_SCHEME;
    u32 scheme_version = 1;
    char scheme_uri[] = "http://example.com/scheme";
    char kms_URI[] = "http://example.com/kms";
    Bool selective_encryption = GF_FALSE;
    u32 KI_length = 0;
    u32 IV_length = 0;

    gf_isom_set_ismacryp_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, scheme_uri, kms_URI, selective_encryption, KI_length, IV_length);
}

static void fuzz_gf_isom_is_ismacryp_media(GF_ISOFile *isom_file) {
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;

    gf_isom_is_ismacryp_media(isom_file, trackNumber, sampleDescriptionIndex);
}

int LLVMFuzzerTestOneInput_225(const uint8_t *Data, size_t Size) {
    // Allocate memory for GF_ISOFile as a generic block of memory
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(1024); // Use a placeholder size
    if (!isom_file) return 0;

    memset(isom_file, 0, 1024); // Use the same placeholder size

    fuzz_gf_isom_ismacryp_delete_sample();
    fuzz_gf_isom_get_ismacryp_sample(isom_file);
    fuzz_gf_isom_ismacryp_sample_from_data(Data, Size);
    fuzz_gf_isom_set_ismacryp_protection(isom_file);
    fuzz_gf_isom_is_ismacryp_media(isom_file);

    free(isom_file);
    return 0;
}