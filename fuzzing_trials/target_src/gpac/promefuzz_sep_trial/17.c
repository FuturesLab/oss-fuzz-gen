// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_user_data at isom_read.c:2769:8 in isomedia.h
// gf_isom_get_track_template at isom_write.c:4137:8 in isomedia.h
// gf_isom_get_stsd_template at isom_write.c:4310:8 in isomedia.h
// gf_isom_get_jp2_config at isom_read.c:6095:8 in isomedia.h
// gf_isom_opus_config_get at sample_descs.c:551:8 in isomedia.h
// gf_isom_update_sample_description_from_template at isom_write.c:8597:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = 0;
    u32 UserDataType = 0;
    bin128 UUID = {0};
    u32 UserDataIndex = 0;
    u8 *userData = NULL;
    u32 userDataSize = 0;

    u8 *output = NULL;
    u32 output_size = 0;

    u32 sampleDescriptionIndex = 0;
    u8 *dsi = NULL;
    u32 dsi_size = 0;

    // gf_isom_get_user_data
    GF_Err err = gf_isom_get_user_data(isom_file, trackNumber, UserDataType, UUID, UserDataIndex, &userData, &userDataSize);
    if (err == GF_OK && userData) {
        free(userData);
    }

    // gf_isom_get_track_template
    err = gf_isom_get_track_template(isom_file, trackNumber, &output, &output_size);
    if (err == GF_OK && output) {
        free(output);
    }

    // gf_isom_get_stsd_template
    err = gf_isom_get_stsd_template(isom_file, trackNumber, sampleDescriptionIndex, &output, &output_size);
    if (err == GF_OK && output) {
        free(output);
    }

    // gf_isom_get_jp2_config
    err = gf_isom_get_jp2_config(isom_file, trackNumber, sampleDescriptionIndex, &dsi, &dsi_size);
    if (err == GF_OK && dsi) {
        free(dsi);
    }

    // gf_isom_opus_config_get
    err = gf_isom_opus_config_get(isom_file, trackNumber, sampleDescriptionIndex, &dsi, &dsi_size);
    if (err == GF_OK && dsi) {
        free(dsi);
    }

    // gf_isom_update_sample_description_from_template
    err = gf_isom_update_sample_description_from_template(isom_file, trackNumber, sampleDescriptionIndex, (u8 *)Data, Size);

    cleanup_iso_file(isom_file);
    return 0;
}