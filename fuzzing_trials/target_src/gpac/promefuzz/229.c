// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_remove_stream_description at isom_write.c:909:8 in isomedia.h
// gf_isom_svc_config_del at avc_ext.c:1818:8 in isomedia.h
// gf_isom_ac3_config_update at sample_descs.c:746:8 in isomedia.h
// gf_isom_get_bitrate at isom_read.c:5967:8 in isomedia.h
// gf_isom_get_tmcd_config at sample_descs.c:1953:8 in isomedia.h
// gf_isom_lhvc_force_inband_config at avc_ext.c:2330:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isom_file() {
    // Create a dummy ISO file by opening with a temporary directory
    GF_ISOFile* isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_EDIT, "/tmp");
    return isom_file;
}

static GF_AC3Config* create_dummy_ac3_config() {
    GF_AC3Config* ac3_config = (GF_AC3Config*)malloc(sizeof(GF_AC3Config));
    if (!ac3_config) return NULL;
    memset(ac3_config, 0, sizeof(GF_AC3Config));
    return ac3_config;
}

int LLVMFuzzerTestOneInput_229(const uint8_t *Data, size_t Size) {
    if (Size < 12) return 0;

    GF_ISOFile* isom_file = create_dummy_isom_file();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u32 sampleDescriptionIndex = *((u32*)(Data + 4));

    GF_AC3Config* ac3_config = create_dummy_ac3_config();
    if (!ac3_config) {
        gf_isom_close(isom_file);
        return 0;
    }

    u32 average_bitrate, max_bitrate, decode_buffer_size;
    u32 tmcd_flags, tmcd_fps_num, tmcd_fps_den, tmcd_fpt;

    // Fuzz gf_isom_remove_stream_description
    gf_isom_remove_stream_description(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_svc_config_del
    gf_isom_svc_config_del(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_ac3_config_update
    gf_isom_ac3_config_update(isom_file, trackNumber, sampleDescriptionIndex, ac3_config);

    // Fuzz gf_isom_get_bitrate
    gf_isom_get_bitrate(isom_file, trackNumber, sampleDescriptionIndex, &average_bitrate, &max_bitrate, &decode_buffer_size);

    // Fuzz gf_isom_get_tmcd_config
    gf_isom_get_tmcd_config(isom_file, trackNumber, sampleDescriptionIndex, &tmcd_flags, &tmcd_fps_num, &tmcd_fps_den, &tmcd_fpt);

    // Fuzz gf_isom_lhvc_force_inband_config
    gf_isom_lhvc_force_inband_config(isom_file, trackNumber, sampleDescriptionIndex);

    free(ac3_config);
    gf_isom_close(isom_file);

    return 0;
}