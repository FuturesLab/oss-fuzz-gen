// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_track_template at isom_write.c:4137:8 in isomedia.h
// gf_isom_opus_config_get at sample_descs.c:551:8 in isomedia.h
// gf_isom_get_user_data at isom_read.c:2769:8 in isomedia.h
// gf_isom_update_sample_description_from_template at isom_write.c:8597:8 in isomedia.h
// gf_isom_get_stsd_template at isom_write.c:4310:8 in isomedia.h
// gf_isom_get_jp2_config at isom_read.c:6095:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_205(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = 1; // Arbitrary track number
    u32 sampleDescriptionIndex = 1; // Arbitrary sample description index
    u8 *output = NULL;
    u32 output_size = 0;
    u8 *dsi = NULL;
    u32 dsi_size = 0;
    u8 *userData = NULL;
    u32 userDataSize = 0;
    u8 *out_dsi = NULL;
    u32 out_size = 0;
    bin128 UUID = {0}; // Initialize UUID with zero

    prepare_dummy_file(Data, Size);

    gf_isom_get_track_template(isom_file, trackNumber, &output, &output_size);
    if (output) free(output);

    gf_isom_opus_config_get(isom_file, trackNumber, sampleDescriptionIndex, &dsi, &dsi_size);
    if (dsi) free(dsi);

    gf_isom_get_user_data(isom_file, trackNumber, 0, UUID, 0, &userData, &userDataSize);
    if (userData) free(userData);

    gf_isom_update_sample_description_from_template(isom_file, trackNumber, sampleDescriptionIndex, (u8 *)Data, Size);

    gf_isom_get_stsd_template(isom_file, trackNumber, sampleDescriptionIndex, &output, &output_size);
    if (output) free(output);

    gf_isom_get_jp2_config(isom_file, trackNumber, sampleDescriptionIndex, &out_dsi, &out_size);
    if (out_dsi) free(out_dsi);

    gf_isom_close(isom_file);
    return 0;
}