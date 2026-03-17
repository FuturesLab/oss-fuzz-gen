// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_ac4_config_update at sample_descs.c:815:8 in isomedia.h
// gf_isom_ac4_config_get at sample_descs.c:363:15 in isomedia.h
// gf_isom_ac4_config_new at sample_descs.c:775:8 in isomedia.h
// gf_isom_enum_sample_group at isom_read.c:5256:8 in isomedia.h
// gf_isom_truehd_config_get at sample_descs.c:416:8 in isomedia.h
// gf_isom_update_bitrate at sample_descs.c:1776:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file object
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static GF_AC4Config* create_dummy_ac4_config() {
    GF_AC4Config *cfg = malloc(sizeof(GF_AC4Config));
    if (!cfg) return NULL;
    memset(cfg, 0, sizeof(GF_AC4Config));
    return cfg;
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    // Ensure we have enough data for the first few u32 reads
    if (Size < sizeof(u32) * 5) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    GF_AC4Config *ac4_cfg = create_dummy_ac4_config();
    if (!ac4_cfg) {
        gf_isom_close(iso_file);
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 sgrp_idx = 0;
    u32 sgrp_type, sgrp_flags, sgrp_parameter, sgrp_size;
    u8 *sgrp_data = NULL;
    u32 format_info, peak_data_rate;
    u32 average_bitrate = *(u32 *)(Data + 2 * sizeof(u32));
    u32 max_bitrate = *(u32 *)(Data + 3 * sizeof(u32));
    u32 decode_buffer_size = *(u32 *)(Data + 4 * sizeof(u32));

    // Fuzz gf_isom_ac4_config_update
    gf_isom_ac4_config_update(iso_file, trackNumber, sampleDescriptionIndex, ac4_cfg);

    // Fuzz gf_isom_ac4_config_get
    GF_AC4Config *retrieved_cfg = gf_isom_ac4_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (retrieved_cfg) {
        // In a real scenario, we might want to do something with retrieved_cfg
    }

    // Fuzz gf_isom_ac4_config_new
    u32 outDescriptionIndex;
    gf_isom_ac4_config_new(iso_file, trackNumber, ac4_cfg, NULL, NULL, &outDescriptionIndex);

    // Fuzz gf_isom_enum_sample_group
    gf_isom_enum_sample_group(iso_file, trackNumber, sampleDescriptionIndex, &sgrp_idx, &sgrp_type, &sgrp_flags, &sgrp_parameter, &sgrp_data, &sgrp_size);
    free(sgrp_data);

    // Fuzz gf_isom_truehd_config_get
    gf_isom_truehd_config_get(iso_file, trackNumber, sampleDescriptionIndex, &format_info, &peak_data_rate);

    // Fuzz gf_isom_update_bitrate
    gf_isom_update_bitrate(iso_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);

    free(ac4_cfg);
    gf_isom_close(iso_file);

    return 0;
}