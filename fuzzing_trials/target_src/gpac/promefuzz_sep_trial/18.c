// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_has_cenc_sample_group at isom_read.c:5020:6 in isomedia.h
// gf_isom_new_track_from_template at isom_write.c:640:5 in isomedia.h
// gf_isom_is_track_encrypted at isom_read.c:1624:6 in isomedia.h
// gf_isom_get_sample_cenc_info at isom_read.c:5790:8 in isomedia.h
// gf_isom_get_meta_type at meta.c:43:5 in isomedia.h
// gf_isom_is_cenc_media at drm_sample.c:681:6 in isomedia.h
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

static GF_ISOFile* create_dummy_iso_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(data, 1, size, file);
    fclose(file);
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *(((u32 *)Data) + 1);
    u32 sampleDescriptionIndex = *(((u32 *)Data) + 2);
    Bool has_selective, has_roll, is_encrypted;
    u32 crypt_byte_block, skip_byte_block, key_info_size;
    const u8 *key_info;
    GF_Err err;

    // Test gf_isom_has_cenc_sample_group
    gf_isom_has_cenc_sample_group(isom_file, trackNumber, &has_selective, &has_roll);

    // Test gf_isom_new_track_from_template
    u32 trakID = 0;
    u32 MediaType = *((u32 *)Data);
    u32 TimeScale = *((u32 *)Data);
    u8 *tk_box = (u8 *)Data;
    u32 tk_box_size = Size;
    Bool udta_only = GF_FALSE;
    gf_isom_new_track_from_template(isom_file, trakID, MediaType, TimeScale, tk_box, tk_box_size, udta_only);

    // Test gf_isom_is_track_encrypted
    gf_isom_is_track_encrypted(isom_file, trackNumber);

    // Test gf_isom_get_sample_cenc_info
    err = gf_isom_get_sample_cenc_info(isom_file, trackNumber, sampleNumber, &is_encrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);

    // Test gf_isom_get_meta_type
    Bool root_meta = GF_TRUE;
    gf_isom_get_meta_type(isom_file, root_meta, trackNumber);

    // Test gf_isom_is_cenc_media
    gf_isom_is_cenc_media(isom_file, trackNumber, sampleDescriptionIndex);

    gf_isom_close(isom_file);
    return 0;
}