// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_generic_protection at drm_sample.c:626:8 in isomedia.h
// gf_isom_get_data_reference at isom_read.c:1723:8 in isomedia.h
// gf_isom_get_ismacryp_info at drm_sample.c:257:8 in isomedia.h
// gf_isom_av1_config_new at avc_ext.c:2007:8 in isomedia.h
// gf_isom_set_media_language at isom_write.c:297:8 in isomedia.h
// gf_isom_change_ismacryp_protection at drm_sample.c:386:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static void destroy_dummy_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_249(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = Size > 0 ? Data[0] : 0;
    u32 sampleDescriptionIndex = Size > 1 ? Data[1] : 0;
    u32 scheme_type = Size > 2 ? Data[2] : 0;
    u32 scheme_version = Size > 3 ? Data[3] : 0;

    char *scheme_uri = NULL;
    char *kms_URI = NULL;
    if (Size > 4) {
        scheme_uri = (char *)malloc(Size - 4);
        if (scheme_uri) {
            memcpy(scheme_uri, Data + 4, Size - 4);
        }
    }

    GF_Err err = gf_isom_set_generic_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, scheme_uri, kms_URI);

    const char *outURL = NULL;
    const char *outURN = NULL;
    err = gf_isom_get_data_reference(isom_file, trackNumber, sampleDescriptionIndex, &outURL, &outURN);

    u32 outOriginalFormat = 0;
    u32 outSchemeType = 0;
    u32 outSchemeVersion = 0;
    const char *outSchemeURI = NULL;
    const char *outKMS_URI = NULL;
    Bool outSelectiveEncryption = 0;
    u32 outIVLength = 0;
    u32 outKeyIndicationLength = 0;
    err = gf_isom_get_ismacryp_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion, &outSchemeURI, &outKMS_URI, &outSelectiveEncryption, &outIVLength, &outKeyIndicationLength);

    GF_AV1Config *cfg = NULL;
    u32 outDescriptionIndex = 0;
    err = gf_isom_av1_config_new(isom_file, trackNumber, cfg, outURL, outURN, &outDescriptionIndex);

    char *code = (Size > 5) ? (char *)malloc(Size - 5) : NULL;
    if (code) {
        memcpy(code, Data + 5, Size - 5);
    }
    err = gf_isom_set_media_language(isom_file, trackNumber, code);

    err = gf_isom_change_ismacryp_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_uri, kms_URI);

    if (scheme_uri) free(scheme_uri);
    if (code) free(code);
    destroy_dummy_iso_file(isom_file);

    return 0;
}