// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_remove_user_data at isom_write.c:3758:8 in isomedia.h
// gf_isom_set_sample_padding at isom_read.c:2492:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_get_user_data at isom_read.c:2769:8 in isomedia.h
// gf_isom_probe_data at isom_read.c:195:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void initialize_uuid(bin128 UUID) {
    for (int i = 0; i < 16; i++) {
        UUID[i] = rand() % 256;
    }
}

static GF_ISOFile* create_dummy_iso_file() {
    return NULL; // Returning NULL for simplicity as we cannot allocate an incomplete type
}

int LLVMFuzzerTestOneInput_216(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();

    u32 trackNumber = Data[0];
    u32 UserDataType = Data[1];
    u32 padding_bytes = Data[2];
    u32 sampleNumber = Data[3];
    u32 sampleDescIndex = Data[4];
    u32 UserDataIndex = Data[5];
    u32 container_type = 0;
    u32 outSize = 0;
    u8 *out_buffer = NULL;
    u8 *userData = NULL;
    u32 userDataSize = 0;
    bin128 UUID;
    initialize_uuid(UUID);

    gf_isom_remove_user_data(isom_file, trackNumber, UserDataType, UUID);
    gf_isom_set_sample_padding(isom_file, trackNumber, padding_bytes);
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);
    gf_isom_get_user_data(isom_file, trackNumber, UserDataType, UUID, UserDataIndex, &userData, &userDataSize);
    gf_isom_probe_data(Data, Size);

    if (out_buffer) {
        free(out_buffer);
    }
    if (userData) {
        free(userData);
    }

    return 0;
}