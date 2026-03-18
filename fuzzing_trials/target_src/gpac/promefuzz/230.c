// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_track_cenc_add_sample_info at drm_sample.c:1309:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_get_sample_cenc_info at isom_read.c:5790:8 in isomedia.h
// gf_isom_ismacryp_sample_from_data at drm_sample.c:48:16 in isomedia.h
// gf_isom_fragment_add_subsample at movie_fragments.c:3133:8 in isomedia.h
// gf_isom_extract_meta_item_get_cenc_info at meta.c:506:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"
#define TMP_DIR "/tmp"

// Helper function to create a dummy ISO file
static GF_ISOFile* create_dummy_iso_file() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // We will assume some hypothetical initialization function exists.
    GF_ISOFile *file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, TMP_DIR);
    return file;
}

// Helper function to free a dummy ISO file
static void free_dummy_iso_file(GF_ISOFile *file) {
    if (file) gf_isom_close(file);
}

int LLVMFuzzerTestOneInput_230(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 10) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Extract parameters for gf_isom_set_cenc_protection
    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + 4));
    u32 scheme_type = *((u32 *)(Data + 8));
    u32 scheme_version = *((u32 *)(Data + 12));
    u32 default_IsEncrypted = *((u32 *)(Data + 16));
    u32 default_crypt_byte_block = *((u32 *)(Data + 20));
    u32 default_skip_byte_block = *((u32 *)(Data + 24));
    u8 *key_info = (u8 *)(Data + 28);
    u32 key_info_size = (Size > 28) ? (Size - 28) : 0;

    gf_isom_set_cenc_protection(iso_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version,
                                default_IsEncrypted, default_crypt_byte_block, default_skip_byte_block,
                                key_info, key_info_size);

    // Extract parameters for gf_isom_get_sample_cenc_info
    u32 sampleNumber = *((u32 *)(Data + 4));
    Bool IsEncrypted;
    u32 crypt_byte_block;
    u32 skip_byte_block;
    const u8 *retrieved_key_info;
    u32 retrieved_key_info_size;

    gf_isom_get_sample_cenc_info(iso_file, trackNumber, sampleNumber, &IsEncrypted, &crypt_byte_block,
                                 &skip_byte_block, &retrieved_key_info, &retrieved_key_info_size);

    // Extract parameters for gf_isom_ismacryp_sample_from_data
    u8 *sample_data = (u8 *)(Data + 28);
    u32 dataLength = (Size > 28) ? (Size - 28) : 0;
    Bool use_selective_encryption = *((Bool *)(Data + 8));
    u8 KI_length = *((u8 *)(Data + 9));
    u8 IV_length = *((u8 *)(Data + 10));

    GF_ISMASample *isma_sample = gf_isom_ismacryp_sample_from_data(sample_data, dataLength, use_selective_encryption, KI_length, IV_length);
    if (isma_sample) free(isma_sample);

    // Extract parameters for gf_isom_fragment_add_subsample
    GF_ISOTrackID TrackID = *((GF_ISOTrackID *)(Data + 4));
    u32 flags = *((u32 *)(Data + 8));
    u32 subSampleSize = *((u32 *)(Data + 12));
    u8 priority = *((u8 *)(Data + 16));
    u32 reserved = *((u32 *)(Data + 17));
    Bool discardable = *((Bool *)(Data + 21));

    gf_isom_fragment_add_subsample(iso_file, TrackID, flags, subSampleSize, priority, reserved, discardable);

    // Extract parameters for gf_isom_extract_meta_item_get_cenc_info
    Bool root_meta = *((Bool *)(Data + 8));
    u32 item_id = *((u32 *)(Data + 12));
    Bool is_protected;
    u32 skip_byte_block_meta;
    u32 crypt_byte_block_meta;
    const u8 *key_info_meta;
    u32 key_info_size_meta;
    u32 aux_info_type_parameter;
    u8 *sai_out_data = NULL;
    u32 sai_out_size;
    u32 sai_out_alloc_size;

    gf_isom_extract_meta_item_get_cenc_info(iso_file, root_meta, trackNumber, item_id, &is_protected,
                                            &skip_byte_block_meta, &crypt_byte_block_meta, &key_info_meta,
                                            &key_info_size_meta, &aux_info_type_parameter, &sai_out_data,
                                            &sai_out_size, &sai_out_alloc_size);
    if (sai_out_data) free(sai_out_data);

    // Extract parameters for gf_isom_track_cenc_add_sample_info
    u32 container_type = *((u32 *)(Data + 8));
    u8 *buf = (u8 *)(Data + 28);
    u32 len = (Size > 28) ? (Size - 28) : 0;
    Bool use_subsamples = *((Bool *)(Data + 12));
    Bool use_saio_32bit = *((Bool *)(Data + 13));
    Bool is_multi_key = *((Bool *)(Data + 14));

    gf_isom_track_cenc_add_sample_info(iso_file, trackNumber, container_type, buf, len, use_subsamples, use_saio_32bit, is_multi_key);

    free_dummy_iso_file(iso_file);
    return 0;
}