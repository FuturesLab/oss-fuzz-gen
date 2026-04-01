// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_new_webvtt_description at sample_descs.c:1637:8 in isomedia.h
// gf_isom_stxt_get_description at sample_descs.c:1385:8 in isomedia.h
// gf_isom_set_ismacryp_protection at drm_sample.c:559:8 in isomedia.h
// gf_isom_opus_config_new at sample_descs.c:476:8 in isomedia.h
// gf_isom_sdp_track_get at hint_track.c:937:8 in isomedia.h
// gf_isom_set_oma_protection at drm_sample.c:590:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for the ISO file structure
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static GF_OpusConfig* create_dummy_opus_config() {
    GF_OpusConfig *config = malloc(sizeof(GF_OpusConfig));
    if (config) {
        memset(config, 0, sizeof(GF_OpusConfig));
    }
    return config;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = 1;
    u32 descriptionIndex = 0;
    const char *URLname = NULL;
    const char *URNname = NULL;
    const char *config = (const char *)Data;

    // Fuzz gf_isom_new_webvtt_description
    gf_isom_new_webvtt_description(iso_file, trackNumber, URLname, URNname, &descriptionIndex, config);

    // Fuzz gf_isom_stxt_get_description
    const char *mime = NULL;
    const char *encoding = NULL;
    gf_isom_stxt_get_description(iso_file, trackNumber, descriptionIndex, &mime, &encoding, &config);

    // Fuzz gf_isom_set_ismacryp_protection
    u32 scheme_type = 0;
    u32 scheme_version = 1;
    char *scheme_uri = NULL;
    char *kms_URI = NULL;
    Bool selective_encryption = 0;
    u32 KI_length = 0;
    u32 IV_length = 0;
    gf_isom_set_ismacryp_protection(iso_file, trackNumber, descriptionIndex, scheme_type, scheme_version, scheme_uri, kms_URI, selective_encryption, KI_length, IV_length);

    // Fuzz gf_isom_opus_config_new
    GF_OpusConfig *opus_config = create_dummy_opus_config();
    if (opus_config) {
        gf_isom_opus_config_new(iso_file, trackNumber, opus_config, (char *)URLname, (char *)URNname, &descriptionIndex);
        free(opus_config);
    }

    // Fuzz gf_isom_sdp_track_get
    const char *sdp = NULL;
    u32 sdp_length = 0;
    gf_isom_sdp_track_get(iso_file, trackNumber, &sdp, &sdp_length);

    // Fuzz gf_isom_set_oma_protection
    char *contentID = NULL;
    u32 encryption_type = 0;
    u64 plainTextLength = 0;
    char *textual_headers = NULL;
    u32 textual_headers_len = 0;
    gf_isom_set_oma_protection(iso_file, trackNumber, descriptionIndex, contentID, kms_URI, encryption_type, plainTextLength, textual_headers, textual_headers_len, selective_encryption, KI_length, IV_length);

    gf_isom_close(iso_file);
    return 0;
}