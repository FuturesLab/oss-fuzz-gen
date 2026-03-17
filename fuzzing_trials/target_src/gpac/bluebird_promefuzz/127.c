#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for the GF_ISOFile structure indirectly
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (!iso_file) return;
    gf_isom_close(iso_file);
}

int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Data[0] % 5; // Choose a track number between 0 and 4
    u8 *data = (u8 *)malloc(Size);
    if (data) {
        memcpy(data, Data, Size);
    }

    // Test gf_isom_append_sample_data
    gf_isom_append_sample_data(iso_file, trackNumber, data, Size);

    // Test gf_isom_get_track_template
    u8 *output = NULL;
    u32 output_size = 0;
    gf_isom_get_track_template(iso_file, trackNumber, &output, &output_size);
    free(output);

    // Test gf_isom_get_raw_user_data
    output = NULL;
    output_size = 0;
    gf_isom_get_raw_user_data(iso_file, &output, &output_size);
    free(output);

    // Test gf_isom_set_sample_cenc_group
    u8 isEncrypted = Data[0] % 2;
    u32 crypt_byte_block = Data[0] % 3;
    u32 skip_byte_block = Data[0] % 3;
    u8 *key_info = (u8 *)malloc(20);
    if (key_info) {
        memcpy(key_info, Data, 20 < Size ? 20 : Size);
    }
    gf_isom_set_sample_cenc_group(iso_file, trackNumber, 1, isEncrypted, crypt_byte_block, skip_byte_block, key_info, 20);
    free(key_info);

    // Test gf_isom_cenc_get_sample_aux_info
    u32 container_type = 0;
    output = NULL;
    output_size = 0;
    gf_isom_cenc_get_sample_aux_info(iso_file, trackNumber, 1, 1, &container_type, &output, &output_size);
    free(output);

    // Test gf_isom_hint_blank_data
    u8 AtBegin = Data[0] % 2;
    gf_isom_hint_blank_data(iso_file, trackNumber, AtBegin);

    cleanup_iso_file(iso_file);
    free(data);
    return 0;
}