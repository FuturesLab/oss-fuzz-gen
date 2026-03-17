#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_Err dummy_on_block_out(void *usr_data, u8 *block, u32 block_size, void *cbk_data, u32 cbk_magic) {
    return GF_OK;
}

static GF_Err dummy_on_block_patch(void *usr_data, u8 *block, u32 block_size, u64 block_offset, Bool is_insert) {
    return GF_OK;
}

static void dummy_on_last_block_start(void *usr_data) {
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 19) { // Minimum size to access all Data indices used
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    // Prepare dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    // Fuzz gf_isom_set_sample_flags
    gf_isom_set_sample_flags(isom_file, Data[0], Data[1], Data[2], Data[3], Data[4], Data[5]);

    // Fuzz gf_isom_set_write_callback
    gf_isom_set_write_callback(isom_file, dummy_on_block_out, dummy_on_block_patch, dummy_on_last_block_start, NULL, Data[6]);

    // Fuzz gf_isom_set_media_subtype
    gf_isom_set_media_subtype(isom_file, Data[7], Data[8], Data[9]);

    // Fuzz gf_isom_get_pcm_config
    u32 flags, pcm_size;
    gf_isom_get_pcm_config(isom_file, Data[10], Data[11], &flags, &pcm_size);

    // Fuzz gf_isom_set_visual_info
    gf_isom_set_visual_info(isom_file, Data[12], Data[13], Data[14], Data[15]);

    // Fuzz gf_isom_get_visual_info
    u32 width, height;
    gf_isom_get_visual_info(isom_file, Data[16], Data[17], &width, &height);

    gf_isom_close(isom_file);
    return 0;
}