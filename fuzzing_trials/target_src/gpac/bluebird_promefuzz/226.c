#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_226(const uint8_t *Data, size_t Size) {
    if (Size < 28) {
        return 0;
    } // Ensure enough data for initial parameters

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 UserDataType = *(u32 *)(Data + 4);
    bin128 UUID;
    memcpy(UUID, Data + 8, 16);
    u32 UserDataIndex = *(u32 *)(Data + 24);

    // Fuzz gf_isom_remove_user_data_item
    gf_isom_remove_user_data_item(isom_file, trackNumber, UserDataType, UUID, UserDataIndex);

    // Prepare data for gf_isom_append_sample_data
    if (Size > 28) {
        u8 *sample_data = (u8 *)(Data + 28);
        u32 sample_data_size = (u32)(Size - 28);

        // Fuzz gf_isom_append_sample_data
        gf_isom_append_sample_data(isom_file, trackNumber, sample_data, sample_data_size);
    }

    // Prepare data for gf_isom_setup_track_fragment_template
    if (Size > 32) {
        u8 *boxes = (u8 *)(Data + 32);
        u32 boxes_size = (u32)(Size - 32);
        u8 force_traf_flags = Data[Size - 1];

        // Fuzz gf_isom_setup_track_fragment_template
        gf_isom_setup_track_fragment_template(isom_file, trackNumber, boxes, boxes_size, force_traf_flags);
    }

    // Prepare data for gf_isom_cenc_get_sample_aux_info
    u32 sampleNumber = UserDataType;
    u32 sampleDescIndex = UserDataIndex;
    u32 container_type = 0;
    u8 *out_buffer = NULL;
    u32 outSize = 0;

    // Fuzz gf_isom_cenc_get_sample_aux_info
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);

    // Prepare data for gf_isom_set_track_stsd_templates
    if (Size > 36) {
        u8 *stsd_data = (u8 *)(Data + 36);
        u32 stsd_data_size = (u32)(Size - 36);

        // Fuzz gf_isom_set_track_stsd_templates
        gf_isom_set_track_stsd_templates(isom_file, trackNumber, stsd_data, stsd_data_size);
    }

    // Prepare data for gf_isom_rtp_packet_set_flags
    if (Size > 41) {
        u8 PackingBit = Data[37];
        u8 eXtensionBit = Data[38];
        u8 MarkerBit = Data[39];
        u8 disposable_packet = Data[40];
        u8 IsRepeatedPacket = Data[41];

        // Fuzz gf_isom_rtp_packet_set_flags
        gf_isom_rtp_packet_set_flags(isom_file, trackNumber, PackingBit, eXtensionBit, MarkerBit, disposable_packet, IsRepeatedPacket);
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(isom_file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    free(out_buffer);

    return 0;
}