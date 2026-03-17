// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_load_extra_boxes at isom_write.c:603:8 in isomedia.h
// gf_isom_fragment_set_sample_rap_group at isom_write.c:7720:8 in isomedia.h
// gf_isom_fragment_add_subsample at movie_fragments.c:3133:8 in isomedia.h
// gf_isom_fragment_set_cenc_sai at movie_fragments.c:3005:8 in isomedia.h
// gf_isom_get_sample_cenc_info at isom_read.c:5790:8 in isomedia.h
// gf_isom_set_sample_cenc_group at isom_write.c:7824:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* initialize_isofile() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // Assuming a function or mechanism exists to create or open an ISOFile.
    GF_ISOFile *iso_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_isofile(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = initialize_isofile();
    if (!iso_file) return 0;

    // Fuzzing gf_isom_load_extra_boxes
    u8 *moov_boxes = (u8 *)Data;
    u32 moov_boxes_size = (u32)(Size > 4 ? 4 : Size);
    Bool udta_only = (Bool)(Data[0] % 2);
    gf_isom_load_extra_boxes(iso_file, moov_boxes, moov_boxes_size, udta_only);

    // Fuzzing gf_isom_fragment_set_sample_rap_group
    GF_ISOTrackID trackID = (GF_ISOTrackID)(Data[0]);
    u32 sample_number_in_frag = (u32)(Data[0] % 100);
    Bool is_rap = (Bool)(Data[0] % 2);
    u32 num_leading_samples = (u32)(Data[0] % 10);
    gf_isom_fragment_set_sample_rap_group(iso_file, trackID, sample_number_in_frag, is_rap, num_leading_samples);

    // Fuzzing gf_isom_fragment_add_subsample
    u32 flags = (u32)(Data[0] % 256);
    u32 subSampleSize = (u32)(Data[0] % 100);
    u8 priority = (u8)(Data[0] % 256);
    u32 reserved = (u32)(Data[0] % 1000);
    Bool discardable = (Bool)(Data[0] % 2);
    gf_isom_fragment_add_subsample(iso_file, trackID, flags, subSampleSize, priority, reserved, discardable);

    // Fuzzing gf_isom_fragment_set_cenc_sai
    u8 *sai_b = (u8 *)Data;
    u32 sai_b_size = (u32)(Size > 4 ? 4 : Size);
    Bool use_subsample = (Bool)(Data[0] % 2);
    Bool use_saio_32bit = (Bool)(Data[0] % 2);
    Bool use_multikey = (Bool)(Data[0] % 2);
    gf_isom_fragment_set_cenc_sai(iso_file, trackID, sai_b, sai_b_size, use_subsample, use_saio_32bit, use_multikey);

    // Fuzzing gf_isom_get_sample_cenc_info
    u32 trackNumber = (u32)(Data[0] % 100);
    u32 sampleNumber = (u32)(Data[0] % 100);
    Bool isEncrypted;
    u32 crypt_byte_block;
    u32 skip_byte_block;
    const u8 *key_info;
    u32 key_info_size;
    gf_isom_get_sample_cenc_info(iso_file, trackNumber, sampleNumber, &isEncrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);

    // Fuzzing gf_isom_set_sample_cenc_group
    u8 isEncryptedFlag = (u8)(Data[0] % 2);
    u32 crypt_byte_block_set = (u32)(Data[0] % 10);
    u32 skip_byte_block_set = (u32)(Data[0] % 10);
    u8 *key_info_set = (u8 *)Data;
    u32 key_info_size_set = (u32)(Size > 19 ? 19 : Size);
    gf_isom_set_sample_cenc_group(iso_file, trackNumber, sampleNumber, isEncryptedFlag, crypt_byte_block_set, skip_byte_block_set, key_info_set, key_info_size_set);

    cleanup_isofile(iso_file);
    return 0;
}