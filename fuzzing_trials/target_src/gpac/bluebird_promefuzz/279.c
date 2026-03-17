#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_279(const uint8_t *Data, size_t Size) {
    if (Size < 100) {
        return 0;
    } // Ensure there's enough data

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + 4));
    u32 scheme_type = *((u32 *)(Data + 8));
    u32 scheme_version = *((u32 *)(Data + 12));
    u32 default_IsEncrypted = *((u32 *)(Data + 16));
    u32 default_crypt_byte_block = *((u32 *)(Data + 20));
    u32 default_skip_byte_block = *((u32 *)(Data + 24));
    u8 *key_info = (u8 *)(Data + 28);
    u32 key_info_size = (Size > 28) ? Size - 28 : 0;

    // Fuzz gf_isom_set_cenc_protection
    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version,
                                default_IsEncrypted, default_crypt_byte_block, default_skip_byte_block,
                                key_info, key_info_size);

    // Fuzz gf_isom_piff_allocate_storage
    u32 AlgorithmID = *((u32 *)(Data + 28));
    u8 IV_size = *(Data + 32);
    bin128 KID;
    if (Size > 48) {
        memcpy(KID, Data + 33, 16);
    } else {
        memset(KID, 0, 16);
    }
    gf_isom_piff_allocate_storage(isom_file, trackNumber, AlgorithmID, IV_size, KID);

    // Fuzz gf_isom_get_pssh_count
    gf_isom_get_pssh_count(isom_file);

    // Fuzz gf_isom_cenc_set_pssh
    bin128 systemID;
    if (Size > 64) {
        memcpy(systemID, Data + 49, 16);
    } else {
        memset(systemID, 0, 16);
    }
    u32 version = *((u32 *)(Data + 65));
    u32 KID_count = *((u32 *)(Data + 69));
    bin128 *KID_array = NULL;
    size_t KID_array_size = KID_count * sizeof(bin128);
    if (KID_count > 0 && Size > 73 + KID_array_size) {
        KID_array = (bin128 *)malloc(KID_array_size);
        if (KID_array) {
            memcpy(KID_array, Data + 73, KID_array_size);
        }
    }
    u8 *data = (u8 *)(Data + 73 + KID_array_size);
    u32 len = (Size > 73 + KID_array_size) ? Size - (73 + KID_array_size) : 0;
    u32 pssh_mode = 0;
    if (Size > 73 + KID_array_size + len) {
        pssh_mode = *(Data + 73 + KID_array_size + len);
    }

    gf_isom_cenc_set_pssh(isom_file, systemID, version, KID_count, KID_array, data, len, pssh_mode);

    // Fuzz gf_isom_get_pssh_info
    if (Size > 74 + KID_array_size + len + 4) {
        u32 pssh_index = *((u32 *)(Data + 74 + KID_array_size + len));
        bin128 SystemID;
        u32 out_version;
        u32 out_KID_count;
        const bin128 *KIDs;
        const u8 *private_data;
        u32 private_data_size;

        gf_isom_get_pssh_info(isom_file, pssh_index, SystemID, &out_version, &out_KID_count, &KIDs, &private_data, &private_data_size);
    }

    // Fuzz gf_isom_is_media_encrypted
    gf_isom_is_media_encrypted(isom_file, trackNumber, sampleDescriptionIndex);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_remove_root_od
    gf_isom_remove_root_od(isom_file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    free(KID_array);

    return 0;
}