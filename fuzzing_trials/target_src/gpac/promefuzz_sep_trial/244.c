// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_generic_protection at drm_sample.c:626:8 in isomedia.h
// gf_isom_get_data_reference at isom_read.c:1723:8 in isomedia.h
// gf_isom_change_ismacryp_protection at drm_sample.c:386:8 in isomedia.h
// gf_isom_avs3v_config_new at avc_ext.c:2045:8 in isomedia.h
// gf_isom_set_adobe_protection at drm_sample.c:1846:8 in isomedia.h
// gf_isom_xml_subtitle_get_description at sample_descs.c:1243:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void free_dummy_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_244(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Not enough data to proceed

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u32 sampleDescriptionIndex = Data[1];
    u32 scheme_type = Data[2];
    u32 scheme_version = Data[3];

    // Fuzz gf_isom_set_generic_protection
    char *scheme_uri = NULL;
    char *kms_URI = NULL;
    if (Size > 5) {
        scheme_uri = (char *)&Data[4];
        kms_URI = (char *)&Data[5];
    }
    gf_isom_set_generic_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, scheme_uri, kms_URI);

    // Fuzz gf_isom_get_data_reference
    const char *outURL = NULL;
    const char *outURN = NULL;
    gf_isom_get_data_reference(isom_file, trackNumber, sampleDescriptionIndex, &outURL, &outURN);

    // Fuzz gf_isom_change_ismacryp_protection
    gf_isom_change_ismacryp_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_uri, kms_URI);

    // Fuzz gf_isom_avs3v_config_new
    GF_AVS3VConfig *cfg = (GF_AVS3VConfig *)malloc(sizeof(GF_AVS3VConfig));
    if (cfg) {
        u32 outDescriptionIndex;
        gf_isom_avs3v_config_new(isom_file, trackNumber, cfg, outURL, outURN, &outDescriptionIndex);
        free(cfg);
    }

    // Ensure there is enough data to access Data[4]
    Bool is_selective_enc = (Size > 4) ? (Bool)(Data[4] % 2) : 0;
    char *metadata = NULL;
    u32 len = 0;
    if (Size > 6) {
        metadata = (char *)&Data[6];
        len = Size - 6;
    }
    gf_isom_set_adobe_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, is_selective_enc, metadata, len);

    // Fuzz gf_isom_xml_subtitle_get_description
    const char *xmlnamespace = NULL;
    const char *xml_schema_loc = NULL;
    const char *mimes = NULL;
    gf_isom_xml_subtitle_get_description(isom_file, trackNumber, sampleDescriptionIndex, &xmlnamespace, &xml_schema_loc, &mimes);

    free_dummy_iso_file(isom_file);

    return 0;
}