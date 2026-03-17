#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void track_num_changed_callback(void *udta, u32 old_track_num, u32 new_track_num) {
    // Callback implementation, can be used to log or handle track number changes
}

int LLVMFuzzerTestOneInput_192(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) {
        return 0; // Not enough data to extract necessary parameters
    }

    // Prepare dummy ISO file
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    // Extract parameters from Data
    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 nalu_size_length = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 index = *((u32 *)(Data + 3 * sizeof(u32)));

    // Fuzz gf_isom_set_nalu_length_field
    gf_isom_set_nalu_length_field(isom_file, trackNumber, sampleDescriptionIndex, nalu_size_length);

    // Fuzz gf_isom_lhvc_force_inband_config
    gf_isom_lhvc_force_inband_config(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_set_track_index
    gf_isom_set_track_index(isom_file, trackNumber, index, track_num_changed_callback, NULL);

    // Fuzz gf_isom_remove_cenc_seig_sample_group
    gf_isom_remove_cenc_seig_sample_group(isom_file, trackNumber);

    // Fuzz gf_isom_svc_config_del
    gf_isom_svc_config_del(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_update_sample_description_from_template
    if (Size > sizeof(u32) * 4) {
        gf_isom_update_sample_description_from_template(isom_file, trackNumber, sampleDescriptionIndex, (u8 *)(Data + 4 * sizeof(u32)), Size - 4 * sizeof(u32));
    }

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}