// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_icc_profile at isom_read.c:4019:8 in isomedia.h
// gf_isom_piff_allocate_storage at drm_sample.c:1155:8 in isomedia.h
// gf_isom_cenc_get_default_info at drm_sample.c:1834:8 in isomedia.h
// gf_isom_get_sample_cenc_info at isom_read.c:5790:8 in isomedia.h
// gf_isom_extract_meta_item_get_cenc_info at meta.c:506:8 in isomedia.h
// gf_isom_fragment_set_cenc_sai at movie_fragments.c:3005:8 in isomedia.h
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

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void fuzz_gf_isom_get_icc_profile(GF_ISOFile *isom_file) {
    u32 trackNumber = rand();
    u32 sampleDescriptionIndex = rand();
    Bool icc_restricted;
    const u8 *icc;
    u32 icc_size;
    gf_isom_get_icc_profile(isom_file, trackNumber, sampleDescriptionIndex, &icc_restricted, &icc, &icc_size);
}

static void fuzz_gf_isom_piff_allocate_storage(GF_ISOFile *isom_file) {
    u32 trackNumber = rand();
    u32 AlgorithmID = rand();
    u8 IV_size = rand();
    bin128 KID = {0};
    gf_isom_piff_allocate_storage(isom_file, trackNumber, AlgorithmID, IV_size, KID);
}

static void fuzz_gf_isom_cenc_get_default_info(GF_ISOFile *isom_file) {
    u32 trackNumber = rand();
    u32 sampleDescriptionIndex = rand();
    u32 container_type;
    Bool default_IsEncrypted;
    u32 crypt_byte_block;
    u32 skip_byte_block;
    const u8 *key_info;
    u32 key_info_size;
    gf_isom_cenc_get_default_info(isom_file, trackNumber, sampleDescriptionIndex, &container_type, &default_IsEncrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);
}

static void fuzz_gf_isom_get_sample_cenc_info(GF_ISOFile *isom_file) {
    u32 trackNumber = rand();
    u32 sampleNumber = rand();
    Bool IsEncrypted;
    u32 crypt_byte_block;
    u32 skip_byte_block;
    const u8 *key_info;
    u32 key_info_size;
    gf_isom_get_sample_cenc_info(isom_file, trackNumber, sampleNumber, &IsEncrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);
}

static void fuzz_gf_isom_extract_meta_item_get_cenc_info(GF_ISOFile *isom_file) {
    Bool root_meta = rand() % 2;
    u32 track_num = rand();
    u32 item_id = rand();
    Bool is_protected;
    u32 skip_byte_block;
    u32 crypt_byte_block;
    const u8 *key_info;
    u32 key_info_size;
    u32 aux_info_type_parameter;
    u8 *sai_out_data = NULL;
    u32 sai_out_size;
    u32 sai_out_alloc_size;
    gf_isom_extract_meta_item_get_cenc_info(isom_file, root_meta, track_num, item_id, &is_protected, &skip_byte_block, &crypt_byte_block, &key_info, &key_info_size, &aux_info_type_parameter, &sai_out_data, &sai_out_size, &sai_out_alloc_size);
    if (sai_out_data) free(sai_out_data);
}

static void fuzz_gf_isom_fragment_set_cenc_sai(GF_ISOFile *isom_file) {
    GF_ISOTrackID trackID = rand();
    u8 *sai_b = NULL;
    u32 sai_b_size = 0;
    Bool use_subsample = rand() % 2;
    Bool use_saio_32bit = rand() % 2;
    Bool use_multikey = rand() % 2;
    gf_isom_fragment_set_cenc_sai(isom_file, trackID, sai_b, sai_b_size, use_subsample, use_saio_32bit, use_multikey);
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    fuzz_gf_isom_get_icc_profile(isom_file);
    fuzz_gf_isom_piff_allocate_storage(isom_file);
    fuzz_gf_isom_cenc_get_default_info(isom_file);
    fuzz_gf_isom_get_sample_cenc_info(isom_file);
    fuzz_gf_isom_extract_meta_item_get_cenc_info(isom_file);
    fuzz_gf_isom_fragment_set_cenc_sai(isom_file);

    gf_isom_close(isom_file);
    return 0;
}