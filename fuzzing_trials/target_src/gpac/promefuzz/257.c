// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_piff_allocate_storage at drm_sample.c:1155:8 in isomedia.h
// gf_isom_get_pssh_count at isom_read.c:5559:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_cenc_set_pssh at drm_sample.c:886:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_pssh_info at isom_read.c:5611:8 in isomedia.h
// gf_isom_is_media_encrypted at drm_sample.c:193:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_257(const uint8_t *Data, size_t Size) {
    if (Size < 4 * sizeof(u32) + sizeof(bin128) + 1) {
        return 0;
    }

    // Create a dummy ISOFile structure
    write_dummy_file(Data, Size);
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)(Data);
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 scheme_type = *(u32 *)(Data + 2 * sizeof(u32));
    u32 scheme_version = *(u32 *)(Data + 3 * sizeof(u32));
    u32 default_IsEncrypted = *(u32 *)(Data + 4 * sizeof(u32));
    u32 default_crypt_byte_block = *(u32 *)(Data + 5 * sizeof(u32));
    u32 default_skip_byte_block = *(u32 *)(Data + 6 * sizeof(u32));
    u8 *key_info = (u8 *)(Data + 7 * sizeof(u32));
    u32 key_info_size = Size - 7 * sizeof(u32);

    // Call gf_isom_set_cenc_protection
    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type,
                                scheme_version, default_IsEncrypted, default_crypt_byte_block,
                                default_skip_byte_block, key_info, key_info_size);

    // Prepare for gf_isom_piff_allocate_storage
    if (Size < sizeof(u32) + sizeof(u8) + sizeof(bin128)) {
        gf_isom_close(isom_file);
        return 0;
    }
    u32 AlgorithmID = *(u32 *)(Data);
    u8 IV_size = *(u8 *)(Data + sizeof(u32));
    bin128 KID;
    memcpy(KID, Data + sizeof(u32) + sizeof(u8), sizeof(bin128));

    // Call gf_isom_piff_allocate_storage
    gf_isom_piff_allocate_storage(isom_file, trackNumber, AlgorithmID, IV_size, KID);

    // Call gf_isom_get_pssh_count
    gf_isom_get_pssh_count(isom_file);

    // Call gf_isom_cenc_set_pssh
    if (Size < sizeof(bin128) + 3 * sizeof(u32) + sizeof(bin128) + 1) {
        gf_isom_close(isom_file);
        return 0;
    }
    bin128 systemID;
    memcpy(systemID, Data, sizeof(bin128));
    u32 version = *(u32 *)(Data + sizeof(bin128));
    u32 KID_count = *(u32 *)(Data + sizeof(bin128) + sizeof(u32));
    bin128 *KIDs = (bin128 *)(Data + sizeof(bin128) + 2 * sizeof(u32));
    u8 *data = (u8 *)(Data + sizeof(bin128) + 2 * sizeof(u32) + sizeof(bin128));
    u32 len = Size - (sizeof(bin128) + 2 * sizeof(u32) + sizeof(bin128));
    u32 pssh_mode = *(u32 *)(Data + sizeof(bin128) + 3 * sizeof(u32) + sizeof(bin128));

    gf_isom_cenc_set_pssh(isom_file, systemID, version, KID_count, KIDs, data, len, pssh_mode);

    // Call gf_isom_get_pssh_info
    if (Size < sizeof(u32) + sizeof(bin128) + 2 * sizeof(u32) + sizeof(bin128) + 1) {
        gf_isom_close(isom_file);
        return 0;
    }
    u32 pssh_index = *(u32 *)(Data);
    bin128 SystemID;
    memcpy(SystemID, Data + sizeof(u32), sizeof(bin128));
    u32 version_out;
    u32 KID_count_out;
    const bin128 *KIDs_out;
    const u8 *private_data;
    u32 private_data_size;

    gf_isom_get_pssh_info(isom_file, pssh_index, SystemID, &version_out, &KID_count_out, &KIDs_out, &private_data, &private_data_size);

    // Call gf_isom_is_media_encrypted
    gf_isom_is_media_encrypted(isom_file, trackNumber, sampleDescriptionIndex);

    gf_isom_close(isom_file);
    return 0;
}