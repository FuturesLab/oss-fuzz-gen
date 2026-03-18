// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_opus_config_get_desc at sample_descs.c:557:8 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_set_sample_cenc_default_group at isom_write.c:7843:8 in isomedia.h
// gf_isom_get_cenc_info at drm_sample.c:726:8 in isomedia.h
// gf_isom_rtp_set_timescale at hint_track.c:226:8 in isomedia.h
// gf_isom_copy_sample_info at isom_write.c:8078:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_287(const uint8_t *Data, size_t Size) {
    // Create a dummy ISO file and other structures
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    GF_OpusConfig opcfg;
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    u32 scheme_type = 0;
    u32 scheme_version = 1;
    u32 default_IsEncrypted = 0;
    u32 default_crypt_byte_block = 0;
    u32 default_skip_byte_block = 0;
    u8 *key_info = (u8 *)Data;
    u32 key_info_size = Size;
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;
    u32 TimeScale = 90000;
    GF_ISOFile *dst = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    GF_ISOFile *src = isom_file;
    u32 dst_track = 1;
    u32 src_track = 1;
    u32 sampleNumber = 1;

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Invoke the target functions
    gf_isom_opus_config_get_desc(isom_file, trackNumber, sampleDescriptionIndex, &opcfg);
    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, default_IsEncrypted, default_crypt_byte_block, default_skip_byte_block, key_info, key_info_size);
    gf_isom_set_sample_cenc_default_group(isom_file, trackNumber, sampleNumber);
    gf_isom_get_cenc_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion);
    gf_isom_rtp_set_timescale(isom_file, trackNumber, sampleDescriptionIndex, TimeScale);
    gf_isom_copy_sample_info(dst, dst_track, src, src_track, sampleNumber);

    // Clean up
    gf_isom_close(isom_file);
    gf_isom_close(dst);

    return 0;
}