// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_ismacryp_sample_from_data at drm_sample.c:48:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_ismacryp_new_sample at drm_sample.c:31:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_get_ismacryp_sample at drm_sample.c:159:16 in isomedia.h
// gf_isom_ismacryp_delete_sample at drm_sample.c:39:6 in isomedia.h
// gf_isom_set_ismacryp_protection at drm_sample.c:559:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_291(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = NULL;

    // Create a dummy ISO file if necessary for testing
    iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!iso_file) {
        return 0;
    }

    // Fuzz gf_isom_is_ismacryp_media
    if (Size >= sizeof(u32) * 2) {
        u32 trackNumber = *(u32 *)Data;
        u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
        Bool result = gf_isom_is_ismacryp_media(iso_file, trackNumber, sampleDescriptionIndex);
    }

    // Fuzz gf_isom_ismacryp_sample_from_data
    if (Size >= sizeof(u32) + 3) {
        u32 dataLength = *(u32 *)Data;
        Bool use_selective_encryption = Data[sizeof(u32)] % 2;
        u8 KI_length = Data[sizeof(u32) + 1];
        u8 IV_length = Data[sizeof(u32) + 2];
        u8 *sample_data = (u8 *)(Data + sizeof(u32) + 3);
        GF_ISMASample *sample = gf_isom_ismacryp_sample_from_data(sample_data, dataLength, use_selective_encryption, KI_length, IV_length);
        if (sample) {
            gf_isom_ismacryp_delete_sample(sample);
        }
    }

    // Fuzz gf_isom_ismacryp_new_sample
    GF_ISMASample *new_sample = gf_isom_ismacryp_new_sample();
    if (new_sample) {
        gf_isom_ismacryp_delete_sample(new_sample);
    }

    // Fuzz gf_isom_get_ismacryp_sample
    if (Size >= sizeof(u32) * 3) {
        u32 trackNumber = *(u32 *)Data;
        u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
        GF_ISOSample samp;
        memset(&samp, 0, sizeof(GF_ISOSample));
        GF_ISMASample *decoded_sample = gf_isom_get_ismacryp_sample(iso_file, trackNumber, &samp, sampleDescriptionIndex);
        if (decoded_sample) {
            gf_isom_ismacryp_delete_sample(decoded_sample);
        }
    }

    // Fuzz gf_isom_set_ismacryp_protection
    if (Size >= sizeof(u32) * 5 + 2) {
        u32 trackNumber = *(u32 *)Data;
        u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
        u32 scheme_type = *(u32 *)(Data + sizeof(u32) * 2);
        u32 scheme_version = *(u32 *)(Data + sizeof(u32) * 3);
        Bool selective_encryption = Data[sizeof(u32) * 4] % 2;
        u32 KI_length = Data[sizeof(u32) * 4 + 1];
        u32 IV_length = Data[sizeof(u32) * 4 + 2];
        char *scheme_uri = "dummy_scheme_uri";
        char *kms_URI = "dummy_kms_URI";
        GF_Err err = gf_isom_set_ismacryp_protection(iso_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, scheme_uri, kms_URI, selective_encryption, KI_length, IV_length);
    }

    gf_isom_close(iso_file);
    return 0;
}