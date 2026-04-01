// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_remove_user_data_item at isom_write.c:3705:8 in isomedia.h
// gf_isom_remove_user_data at isom_write.c:3758:8 in isomedia.h
// gf_isom_hint_direct_data at hint_track.c:441:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_rtp_packet_set_flags at hint_track.c:579:8 in isomedia.h
// gf_isom_add_user_data_boxes at isom_write.c:3856:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void initialize_uuid(bin128 UUID) {
    for (int i = 0; i < 16; i++) {
        UUID[i] = rand() % 256;
    }
}

int LLVMFuzzerTestOneInput_253(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5 + sizeof(bin128) + 14) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 offset = 0;
    u32 trackNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    u32 UserDataType = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    bin128 UUID;
    memcpy(UUID, Data + offset, sizeof(bin128));
    offset += sizeof(bin128);
    u32 UserDataIndex = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    u32 sampleNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    u32 sampleDescIndex = *(u32 *)(Data + offset);
    offset += sizeof(u32);
    u32 container_type = 0;
    u8 *out_buffer = NULL;
    u32 outSize = 0;
    u8 *data = (u8 *)(Data + offset);
    u32 dataLength = Size - offset - 1;
    u8 AtBegin = Data[Size - 1];

    // Test gf_isom_remove_user_data_item
    gf_isom_remove_user_data_item(isom_file, trackNumber, UserDataType, UUID, UserDataIndex);

    // Test gf_isom_remove_user_data
    gf_isom_remove_user_data(isom_file, trackNumber, UserDataType, UUID);

    // Test gf_isom_hint_direct_data
    if (dataLength <= 14) {
        gf_isom_hint_direct_data(isom_file, trackNumber, data, dataLength, AtBegin);
    }

    // Test gf_isom_cenc_get_sample_aux_info
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);
    free(out_buffer);

    // Test gf_isom_rtp_packet_set_flags
    u8 PackingBit = Data[0] & 1;
    u8 eXtensionBit = (Data[0] >> 1) & 1;
    u8 MarkerBit = (Data[0] >> 2) & 1;
    u8 disposable_packet = (Data[0] >> 3) & 1;
    u8 IsRepeatedPacket = (Data[0] >> 4) & 1;
    gf_isom_rtp_packet_set_flags(isom_file, trackNumber, PackingBit, eXtensionBit, MarkerBit, disposable_packet, IsRepeatedPacket);

    // Test gf_isom_add_user_data_boxes
    gf_isom_add_user_data_boxes(isom_file, trackNumber, data, dataLength);

    gf_isom_close(isom_file);
    return 0;
}