// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_icc_profile at isom_read.c:4019:8 in isomedia.h
// gf_isom_extract_meta_item_get_cenc_info at meta.c:506:8 in isomedia.h
// gf_isom_piff_allocate_storage at drm_sample.c:1155:8 in isomedia.h
// gf_isom_cenc_get_default_info at drm_sample.c:1834:8 in isomedia.h
// gf_isom_fragment_set_cenc_sai at movie_fragments.c:3005:8 in isomedia.h
// gf_isom_get_sample_cenc_info at isom_read.c:5790:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(Bool) + sizeof(u8) + sizeof(bin128) + sizeof(GF_ISOTrackID) + sizeof(u32) + 3) {
        return 0;
    }

    prepare_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)(Data);
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    Bool icc_restricted;
    const u8 *icc;
    u32 icc_size;

    GF_Err err = gf_isom_get_icc_profile(isom_file, trackNumber, sampleDescriptionIndex, &icc_restricted, &icc, &icc_size);

    Bool root_meta = (Bool)(Data[8] % 2);
    u32 item_id = *(u32 *)(Data + 9);
    Bool is_protected;
    u32 skip_byte_block, crypt_byte_block;
    const u8 *key_info;
    u32 key_info_size;
    u32 aux_info_type_parameter;
    u8 *sai_out_data = NULL;
    u32 sai_out_size, sai_out_alloc_size;

    err = gf_isom_extract_meta_item_get_cenc_info(isom_file, root_meta, trackNumber, item_id, &is_protected,
                                                  &skip_byte_block, &crypt_byte_block, &key_info, &key_info_size,
                                                  &aux_info_type_parameter, &sai_out_data, &sai_out_size, &sai_out_alloc_size);

    u32 AlgorithmID = *(u32 *)(Data + 13);
    u8 IV_size = Data[17];
    bin128 KID;
    memcpy(&KID, Data + 18, sizeof(bin128));

    err = gf_isom_piff_allocate_storage(isom_file, trackNumber, AlgorithmID, IV_size, KID);

    u32 container_type;
    Bool default_IsEncrypted;

    err = gf_isom_cenc_get_default_info(isom_file, trackNumber, sampleDescriptionIndex, &container_type, &default_IsEncrypted,
                                        &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);

    GF_ISOTrackID trackID = *(GF_ISOTrackID *)(Data + 34);
    u8 *sai_b = (u8 *)(Data + 38);
    u32 sai_b_size = *(u32 *)(Data + 39);
    Bool use_subsample = (Bool)(Data[43] % 2);
    Bool use_saio_32bit = (Bool)(Data[44] % 2);
    Bool use_multikey = (Bool)(Data[45] % 2);

    err = gf_isom_fragment_set_cenc_sai(isom_file, trackID, sai_b, sai_b_size, use_subsample, use_saio_32bit, use_multikey);

    u32 sampleNumber = *(u32 *)(Data + 46);
    Bool IsEncrypted;

    err = gf_isom_get_sample_cenc_info(isom_file, trackNumber, sampleNumber, &IsEncrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);

    gf_isom_close(isom_file);
    return 0;
}