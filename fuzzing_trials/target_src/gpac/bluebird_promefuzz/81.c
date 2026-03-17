#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Prepare dummy file for operations that might require a file
    prepare_dummy_file(Data, Size);

    // Initialize variables for API function calls
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u32 sampleNumber = Data[1];
    u32 grouping_type = *(u32*)(Data + 2);
    u32 grouping_type_parameter = 0;
    u32 sgpd_flags = 0;
    u32 fps_num = 30;
    u32 fps_den = 1;
    s32 frames_per_counter_tick = 0;
    Bool is_drop = GF_FALSE;
    Bool is_counter = GF_FALSE;
    u32 outDescriptionIndex = 0;
    Bool unpack = GF_FALSE;
    Bool root_meta = GF_TRUE;
    u32 item_id = 1;
    u32 group_id = 0;
    u32 group_type = 0;
    GF_ISOTrackID trackID = 1;
    Bool use_subsample = GF_FALSE;
    Bool use_saio_32bit = GF_FALSE;
    Bool use_multikey = GF_FALSE;
    Bool is_rap = GF_FALSE;
    u32 num_leading_samples = 0;

    // Call the target functions with the initialized variables
    gf_isom_set_sample_group_description(isom_file, trackNumber, sampleNumber, grouping_type, grouping_type_parameter, (void*)Data, (u32)Size, sgpd_flags);
    gf_isom_set_cts_packing(isom_file, trackNumber, unpack);
    gf_isom_tmcd_config_new(isom_file, trackNumber, fps_num, fps_den, frames_per_counter_tick, is_drop, is_counter, &outDescriptionIndex);
    gf_isom_meta_add_item_group(isom_file, root_meta, trackNumber, item_id, group_id, group_type);
    gf_isom_fragment_set_cenc_sai(isom_file, trackID, (u8*)Data, (u32)Size, use_subsample, use_saio_32bit, use_multikey);
    gf_isom_set_sample_rap_group(isom_file, trackNumber, sampleNumber, is_rap, num_leading_samples);

    // Clean up
    gf_isom_close(isom_file);
    return 0;
}