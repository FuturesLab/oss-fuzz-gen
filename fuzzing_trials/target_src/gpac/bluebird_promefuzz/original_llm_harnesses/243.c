// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_cenc_info at isom_read.c:5790:8 in isomedia.h
// gf_isom_fragment_set_sample_rap_group at isom_write.c:7720:8 in isomedia.h
// gf_isom_set_sample_cenc_group at isom_write.c:7824:8 in isomedia.h
// gf_isom_load_extra_boxes at isom_write.c:603:8 in isomedia.h
// gf_isom_fragment_add_subsample at movie_fragments.c:3133:8 in isomedia.h
// gf_isom_fragment_set_cenc_sai at movie_fragments.c:3005:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *f = fopen("./dummy_file", "wb");
    if (f) {
        fwrite(Data, 1, Size, f);
        fclose(f);
    }
}

int LLVMFuzzerTestOneInput_243(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0; // Ensure there's enough data

    prepare_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + sizeof(u32)));
    u32 trackID = *((u32 *)(Data + 2 * sizeof(u32)));

    // Variables for gf_isom_get_sample_cenc_info
    Bool isEncrypted;
    u32 crypt_byte_block, skip_byte_block;
    const u8 *key_info;
    u32 key_info_size;

    // Fuzz gf_isom_get_sample_cenc_info
    gf_isom_get_sample_cenc_info(isom_file, trackNumber, sampleNumber, &isEncrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);

    // Fuzz gf_isom_fragment_set_sample_rap_group
    Bool is_rap = (Bool)(Data[0] % 2);
    u32 num_leading_samples = *((u32 *)(Data + 3 * sizeof(u32)));
    gf_isom_fragment_set_sample_rap_group(isom_file, trackID, sampleNumber, is_rap, num_leading_samples);

    // Fuzz gf_isom_set_sample_cenc_group
    u8 isEncryptedFlag = Data[0];
    gf_isom_set_sample_cenc_group(isom_file, trackNumber, sampleNumber, isEncryptedFlag, crypt_byte_block, skip_byte_block, (u8 *)key_info, key_info_size);

    // Fuzz gf_isom_load_extra_boxes
    Bool udta_only = (Bool)(Data[1] % 2);
    gf_isom_load_extra_boxes(isom_file, (u8 *)Data, (u32)Size, udta_only);

    // Fuzz gf_isom_fragment_add_subsample
    u32 flags = *((u32 *)(Data + 4 * sizeof(u32)));
    u32 subSampleSize = *((u32 *)(Data + 5 * sizeof(u32)));
    u8 priority = Data[2];
    u32 reserved = *((u32 *)(Data + 6 * sizeof(u32)));
    Bool discardable = (Bool)(Data[3] % 2);
    gf_isom_fragment_add_subsample(isom_file, trackID, flags, subSampleSize, priority, reserved, discardable);

    // Fuzz gf_isom_fragment_set_cenc_sai
    u8 *sai_b = (u8 *)Data;
    u32 sai_b_size = (u32)Size;
    Bool use_subsample = (Bool)(Data[4] % 2);
    Bool use_saio_32bit = (Bool)(Data[5] % 2);
    Bool use_multikey = (Bool)(Data[6] % 2);
    gf_isom_fragment_set_cenc_sai(isom_file, trackID, sai_b, sai_b_size, use_subsample, use_saio_32bit, use_multikey);

    gf_isom_close(isom_file);
    return 0;
}