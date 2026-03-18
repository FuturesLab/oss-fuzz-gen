// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_remove_user_data_item at isom_write.c:3705:8 in isomedia.h
// gf_isom_add_uuid at isom_write.c:6258:8 in isomedia.h
// gf_isom_append_sample_data at isom_write.c:1218:8 in isomedia.h
// gf_isom_fragment_append_data at movie_fragments.c:3127:8 in isomedia.h
// gf_isom_setup_track_fragment_template at movie_fragments.c:341:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5 + sizeof(bin128)) {
        return 0;
    }

    // Prepare input data
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 UserDataType = *(u32 *)Data;
    Data += sizeof(u32);
    Size -= sizeof(u32);

    bin128 UUID;
    memcpy(UUID, Data, sizeof(bin128));
    Data += sizeof(bin128);
    Size -= sizeof(bin128);

    u32 UserDataIndex = *(u32 *)Data;
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 data_size = *(u32 *)Data;
    Data += sizeof(u32);
    Size -= sizeof(u32);

    // Ensure data_size does not exceed remaining Size
    if (data_size > Size) {
        data_size = Size;
    }

    // Write remaining Data to dummy file
    write_dummy_file(Data, Size);

    // Call gf_isom_remove_user_data_item
    gf_isom_remove_user_data_item(isom_file, trackNumber, UserDataType, UUID, UserDataIndex);

    // Call gf_isom_add_uuid
    gf_isom_add_uuid(isom_file, trackNumber, UUID, Data, data_size);

    // Call gf_isom_append_sample_data
    gf_isom_append_sample_data(isom_file, trackNumber, (u8 *)Data, data_size);

    // Call gf_isom_fragment_append_data
    gf_isom_fragment_append_data(isom_file, trackNumber, (u8 *)Data, data_size, 0);

    // Call gf_isom_setup_track_fragment_template
    gf_isom_setup_track_fragment_template(isom_file, trackNumber, (u8 *)Data, data_size, 0);

    // Prepare buffer for gf_isom_cenc_get_sample_aux_info
    u8 *out_buffer = NULL;
    u32 outSize = 0;
    u32 sampleNumber = 1;
    u32 sampleDescIndex = 1;
    u32 container_type = GF_ISOM_BOX_UUID_PSEC;

    // Call gf_isom_cenc_get_sample_aux_info
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);

    // Free allocated buffer
    if (out_buffer) {
        free(out_buffer);
    }

    // Close the ISO file
    gf_isom_close(isom_file);

    return 0;
}