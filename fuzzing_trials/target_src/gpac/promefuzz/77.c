// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_new_mj2k_description at sample_descs.c:886:8 in isomedia.h
// gf_isom_set_media_language at isom_write.c:297:8 in isomedia.h
// gf_isom_set_generic_protection at drm_sample.c:626:8 in isomedia.h
// gf_isom_change_ismacryp_protection at drm_sample.c:386:8 in isomedia.h
// gf_isom_av1_config_new at avc_ext.c:2007:8 in isomedia.h
// gf_isom_stxt_get_description at sample_descs.c:1385:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Instead of allocating memory, return a NULL pointer to simulate an ISO file
    return NULL;
}

static GF_AV1Config* create_dummy_av1_config() {
    GF_AV1Config *cfg = (GF_AV1Config*)malloc(sizeof(GF_AV1Config));
    if (cfg) {
        memset(cfg, 0, sizeof(GF_AV1Config));
    }
    return cfg;
}

static void cleanup_av1_config(GF_AV1Config *cfg) {
    if (cfg) {
        free(cfg);
    }
}

int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_iso_file();
    GF_AV1Config *av1_config = create_dummy_av1_config();

    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 0;
    u32 outDescriptionIndex = 0;
    char *scheme_uri = NULL;
    char *kms_uri = NULL;
    char *language_code = "eng";
    char *url_name = NULL;
    char *urn_name = NULL;

    // Fuzz gf_isom_new_mj2k_description
    u8 *dsi = (u8*)Data;
    u32 dsi_len = (u32)Size;
    gf_isom_new_mj2k_description(isom_file, trackNumber, url_name, urn_name, &outDescriptionIndex, dsi, dsi_len);

    // Fuzz gf_isom_set_media_language
    gf_isom_set_media_language(isom_file, trackNumber, language_code);

    // Fuzz gf_isom_set_generic_protection
    gf_isom_set_generic_protection(isom_file, trackNumber, sampleDescriptionIndex, 0, 1, scheme_uri, kms_uri);

    // Fuzz gf_isom_change_ismacryp_protection
    gf_isom_change_ismacryp_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_uri, kms_uri);

    // Fuzz gf_isom_av1_config_new
    gf_isom_av1_config_new(isom_file, trackNumber, av1_config, url_name, urn_name, &outDescriptionIndex);

    // Fuzz gf_isom_stxt_get_description
    const char *mime = NULL;
    const char *encoding = NULL;
    const char *config = NULL;
    gf_isom_stxt_get_description(isom_file, trackNumber, sampleDescriptionIndex, &mime, &encoding, &config);

    cleanup_av1_config(av1_config);

    return 0;
}