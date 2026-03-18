// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_fragment_defaults at isom_read.c:2974:8 in isomedia.h
// gf_isom_get_user_data at isom_read.c:2769:8 in isomedia.h
// gf_isom_extract_meta_item_mem at meta.c:500:8 in isomedia.h
// gf_isom_probe_data at isom_read.c:195:5 in isomedia.h
// gf_isom_rtp_packet_set_flags at hint_track.c:579:8 in isomedia.h
// gf_isom_update_sample_description_from_template at isom_write.c:8597:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void fuzz_gf_isom_get_fragment_defaults(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return;
    u32 trackNumber = *(u32*)Data;
    u32 defaultDuration = 0, defaultSize = 0, defaultDescriptionIndex = 0, defaultRandomAccess = 0;
    u8 defaultPadding = 0;
    u16 defaultDegradationPriority = 0;
    gf_isom_get_fragment_defaults(isom_file, trackNumber, &defaultDuration, &defaultSize, &defaultDescriptionIndex, &defaultRandomAccess, &defaultPadding, &defaultDegradationPriority);
}

static void fuzz_gf_isom_get_user_data(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(bin128)) return;
    u32 trackNumber = *(u32*)Data;
    u32 UserDataType = *(u32*)(Data + 4);
    bin128 UUID;
    memcpy(UUID, Data + 8, sizeof(bin128));
    u32 UserDataIndex = *(u32*)(Data + 24);
    u8 *userData = NULL;
    u32 userDataSize = 0;
    gf_isom_get_user_data(isom_file, trackNumber, UserDataType, UUID, UserDataIndex, &userData, &userDataSize);
    if (userData) {
        free(userData);
    }
}

static void fuzz_gf_isom_extract_meta_item_mem(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Bool) + sizeof(u32) * 2) return;
    Bool root_meta = *(Bool*)Data;
    u32 track_num = *(u32*)(Data + 1);
    u32 item_id = *(u32*)(Data + 5);
    u8 *out_data = NULL;
    u32 out_size = 0, out_alloc_size = 0;
    const char *mime_type = NULL;
    Bool use_annex_b = *(Bool*)(Data + 9);
    gf_isom_extract_meta_item_mem(isom_file, root_meta, track_num, item_id, &out_data, &out_size, &out_alloc_size, &mime_type, use_annex_b);
    if (out_data) {
        free(out_data);
    }
}

static void fuzz_gf_isom_probe_data(const uint8_t *Data, size_t Size) {
    gf_isom_probe_data(Data, (u32)Size);
}

static void fuzz_gf_isom_rtp_packet_set_flags(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + 5 * sizeof(u8)) return;
    u32 trackNumber = *(u32*)Data;
    u8 PackingBit = *(u8*)(Data + 4);
    u8 eXtensionBit = *(u8*)(Data + 5);
    u8 MarkerBit = *(u8*)(Data + 6);
    u8 disposable_packet = *(u8*)(Data + 7);
    u8 IsRepeatedPacket = *(u8*)(Data + 8);
    gf_isom_rtp_packet_set_flags(isom_file, trackNumber, PackingBit, eXtensionBit, MarkerBit, disposable_packet, IsRepeatedPacket);
}

static void fuzz_gf_isom_update_sample_description_from_template(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2) return;
    u32 trackNumber = *(u32*)Data;
    u32 sampleDescriptionIndex = *(u32*)(Data + 4);
    gf_isom_update_sample_description_from_template(isom_file, trackNumber, sampleDescriptionIndex, (u8*)(Data + 8), (u32)(Size - 8));
}

int LLVMFuzzerTestOneInput_275(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = gf_isom_open_file("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    fuzz_gf_isom_get_fragment_defaults(isom_file, Data, Size);
    fuzz_gf_isom_get_user_data(isom_file, Data, Size);
    fuzz_gf_isom_extract_meta_item_mem(isom_file, Data, Size);
    fuzz_gf_isom_probe_data(Data, Size);
    fuzz_gf_isom_rtp_packet_set_flags(isom_file, Data, Size);
    fuzz_gf_isom_update_sample_description_from_template(isom_file, Data, Size);

    gf_isom_close(isom_file);
    return 0;
}