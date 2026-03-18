// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_append_sample_data at isom_write.c:1218:8 in isomedia.h
// gf_isom_get_raw_user_data at isom_write.c:4070:8 in isomedia.h
// gf_isom_setup_track_fragment_template at movie_fragments.c:341:8 in isomedia.h
// gf_isom_enum_sample_aux_data at isom_read.c:6524:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_text_get_encoded_tx3g at tx3g.c:950:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void create_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_178(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u8 *data = (u8*)Data;
    u32 data_size = (u32)Size;

    // Fuzz gf_isom_append_sample_data
    gf_isom_append_sample_data(isom_file, trackNumber, data, data_size);

    // Fuzz gf_isom_get_raw_user_data
    u8 *output = NULL;
    u32 output_size = 0;
    gf_isom_get_raw_user_data(isom_file, &output, &output_size);
    free(output);

    // Fuzz gf_isom_setup_track_fragment_template
    gf_isom_setup_track_fragment_template(isom_file, trackNumber, data, data_size, 0);

    // Fuzz gf_isom_enum_sample_aux_data
    u32 sai_idx = 0;
    u32 sai_type = 0;
    u32 sai_parameter = 0;
    u8 *sai_data = NULL;
    u32 sai_size = 0;
    gf_isom_enum_sample_aux_data(isom_file, trackNumber, 0, &sai_idx, &sai_type, &sai_parameter, &sai_data, &sai_size);
    free(sai_data);

    // Fuzz gf_isom_cenc_get_sample_aux_info
    u32 container_type = 0;
    u8 *out_buffer = NULL;
    u32 outSize = 0;
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, 0, 0, &container_type, &out_buffer, &outSize);
    free(out_buffer);

    // Fuzz gf_isom_text_get_encoded_tx3g
    u8 *tx3g = NULL;
    u32 tx3g_size = 0;
    gf_isom_text_get_encoded_tx3g(isom_file, trackNumber, 0, 0, &tx3g, &tx3g_size);
    free(tx3g);

    gf_isom_close(isom_file);
    return 0;
}