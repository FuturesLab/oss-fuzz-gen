// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_add_user_data at isom_write.c:3803:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_reference at isom_read.c:1237:8 in isomedia.h
// gf_isom_cenc_set_pssh at drm_sample.c:886:8 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_get_track_template at isom_write.c:4137:8 in isomedia.h
// gf_isom_get_pssh_info at isom_read.c:5611:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void fuzz_gf_isom_get_reference(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return;

    u32 trackNumber = *((u32 *)Data);
    u32 referenceType = *((u32 *)(Data + sizeof(u32)));
    u32 referenceIndex = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 refTrack;

    gf_isom_get_reference(isom_file, trackNumber, referenceType, referenceIndex, &refTrack);
}

static void fuzz_gf_isom_cenc_set_pssh(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 16 + sizeof(u32) * 3) return;

    bin128 systemID;
    memcpy(systemID, Data, 16);
    u32 version = *((u32 *)(Data + 16));
    u32 KID_count = *((u32 *)(Data + 16 + sizeof(u32)));
    u32 len = *((u32 *)(Data + 16 + sizeof(u32) * 2));
    u32 pssh_mode = *((u32 *)(Data + 16 + sizeof(u32) * 3));

    bin128 *KID = NULL;
    if (KID_count > 0 && Size >= 16 + sizeof(u32) * 3 + KID_count * 16) {
        KID = (bin128 *)(Data + 16 + sizeof(u32) * 4);
    }

    u8 *opaque_data = NULL;
    if (Size >= 16 + sizeof(u32) * 3 + KID_count * 16 + len) {
        opaque_data = (u8 *)(Data + 16 + sizeof(u32) * 4 + KID_count * 16);
    }

    gf_isom_cenc_set_pssh(isom_file, systemID, version, KID_count, KID, opaque_data, len, pssh_mode);
}

static void fuzz_gf_isom_set_cenc_protection(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 8) return;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 scheme_type = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 scheme_version = *((u32 *)(Data + 3 * sizeof(u32)));
    u32 default_IsEncrypted = *((u32 *)(Data + 4 * sizeof(u32)));
    u32 default_crypt_byte_block = *((u32 *)(Data + 5 * sizeof(u32)));
    u32 default_skip_byte_block = *((u32 *)(Data + 6 * sizeof(u32)));
    u32 key_info_size = *((u32 *)(Data + 7 * sizeof(u32)));

    u8 *key_info = NULL;
    if (Size >= sizeof(u32) * 8 + key_info_size) {
        key_info = (u8 *)(Data + sizeof(u32) * 8);
    }

    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version,
                                default_IsEncrypted, default_crypt_byte_block, default_skip_byte_block, key_info, key_info_size);
}

static void fuzz_gf_isom_get_track_template(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return;

    u32 trackNumber = *((u32 *)Data);
    u8 *output = NULL;
    u32 output_size = 0;

    gf_isom_get_track_template(isom_file, trackNumber, &output, &output_size);

    if (output) {
        free(output);
    }
}

static void fuzz_gf_isom_get_pssh_info(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return;

    u32 pssh_index = *((u32 *)Data);
    bin128 SystemID;
    u32 version;
    u32 KID_count;
    const bin128 *KIDs;
    const u8 *private_data;
    u32 private_data_size;

    gf_isom_get_pssh_info(isom_file, pssh_index, SystemID, &version, &KID_count, &KIDs, &private_data, &private_data_size);
}

static void fuzz_gf_isom_add_user_data(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + 16) return;

    u32 trackNumber = *((u32 *)Data);
    u32 UserDataType = *((u32 *)(Data + sizeof(u32)));
    bin128 UUID;
    memcpy(UUID, Data + sizeof(u32) * 2, 16);
    u32 data_size = *((u32 *)(Data + sizeof(u32) * 2 + 16));

    u8 *user_data = NULL;
    if (Size >= sizeof(u32) * 3 + 16 + data_size) {
        user_data = (u8 *)(Data + sizeof(u32) * 3 + 16);
    }

    gf_isom_add_user_data(isom_file, trackNumber, UserDataType, UUID, user_data, data_size);
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);

    if (!isom_file) return 0;

    fuzz_gf_isom_get_reference(isom_file, Data, Size);
    fuzz_gf_isom_cenc_set_pssh(isom_file, Data, Size);
    fuzz_gf_isom_set_cenc_protection(isom_file, Data, Size);
    fuzz_gf_isom_get_track_template(isom_file, Data, Size);
    fuzz_gf_isom_get_pssh_info(isom_file, Data, Size);
    fuzz_gf_isom_add_user_data(isom_file, Data, Size);

    gf_isom_close(isom_file);
    return 0;
}