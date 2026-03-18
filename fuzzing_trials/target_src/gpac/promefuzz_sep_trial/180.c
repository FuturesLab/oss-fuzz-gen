// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_media_type at isom_write.c:6188:8 in isomedia.h
// gf_isom_enum_sample_aux_data at isom_read.c:6524:8 in isomedia.h
// gf_isom_get_raw_user_data at isom_write.c:4070:8 in isomedia.h
// gf_isom_rewrite_track_dependencies at isom_write.c:5120:8 in isomedia.h
// gf_isom_text_get_encoded_tx3g at tx3g.c:950:8 in isomedia.h
// gf_isom_remove_uuid at isom_write.c:6227:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Use a valid temp directory or NULL
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void free_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_180(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 new_type = *((u32 *)(Data + sizeof(u32)));

    // Fuzz gf_isom_set_media_type
    gf_isom_set_media_type(isom_file, trackNumber, new_type);

    if (Size < 3 * sizeof(u32)) {
        free_dummy_iso_file(isom_file);
        return 0;
    }

    u32 sample_number = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 sai_idx = 0;
    u32 sai_type, sai_parameter, sai_size;
    u8 *sai_data = NULL;

    // Fuzz gf_isom_enum_sample_aux_data
    gf_isom_enum_sample_aux_data(isom_file, trackNumber, sample_number, &sai_idx, &sai_type, &sai_parameter, &sai_data, &sai_size);

    free(sai_data);

    u8 *output = NULL;
    u32 output_size;

    // Fuzz gf_isom_get_raw_user_data
    gf_isom_get_raw_user_data(isom_file, &output, &output_size);

    free(output);

    // Fuzz gf_isom_rewrite_track_dependencies
    gf_isom_rewrite_track_dependencies(isom_file, trackNumber);

    if (Size < 4 * sizeof(u32)) {
        free_dummy_iso_file(isom_file);
        return 0;
    }

    u32 sampleDescriptionIndex = *((u32 *)(Data + 3 * sizeof(u32)));
    u32 sidx_offset = *((u32 *)(Data + 4 * sizeof(u32)));
    u8 *tx3g = NULL;
    u32 tx3g_size;

    // Fuzz gf_isom_text_get_encoded_tx3g
    gf_isom_text_get_encoded_tx3g(isom_file, trackNumber, sampleDescriptionIndex, sidx_offset, &tx3g, &tx3g_size);

    free(tx3g);

    if (Size < 4 * sizeof(u32) + 16) {
        free_dummy_iso_file(isom_file);
        return 0;
    }

    bin128 UUID;
    memcpy(UUID, Data + 4 * sizeof(u32), 16);

    // Fuzz gf_isom_remove_uuid
    gf_isom_remove_uuid(isom_file, trackNumber, UUID);

    free_dummy_iso_file(isom_file);
    return 0;
}