// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_hint_sample_description_data at hint_track.c:539:8 in isomedia.h
// gf_isom_get_brands at isom_read.c:2657:12 in isomedia.h
// gf_isom_update_bitrate at sample_descs.c:1776:8 in isomedia.h
// gf_isom_get_stsd_template at isom_write.c:4310:8 in isomedia.h
// gf_isom_get_jp2_config at isom_read.c:6095:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* initialize_iso_file() {
    // Create a dummy file for the purpose of fuzzing
    FILE *dummy_file = fopen(DUMMY_FILE_PATH, "wb");
    if (!dummy_file) return NULL;
    fclose(dummy_file);

    // Assuming there is a function to open a GPAC ISO file
    GF_ISOFile *file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 10) return 0;

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 scheme_type = *(u32 *)(Data + 8);
    u32 scheme_version = *(u32 *)(Data + 12);
    u32 default_IsEncrypted = *(u32 *)(Data + 16);
    u32 default_crypt_byte_block = *(u32 *)(Data + 20);
    u32 default_skip_byte_block = *(u32 *)(Data + 24);
    u32 key_info_size = *(u32 *)(Data + 28);

    // Ensure key_info_size does not exceed the remaining buffer size
    if (Size < 32 + key_info_size) {
        cleanup_iso_file(isom_file);
        return 0;
    }

    u8 *key_info = (u8 *)(Data + 32);

    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type,
                                scheme_version, default_IsEncrypted, default_crypt_byte_block,
                                default_skip_byte_block, key_info, key_info_size);

    if (Size >= 43) {
        u32 SourceTrackID = *(u32 *)(Data + 32);
        u16 DataLength = *(u16 *)(Data + 36);
        u32 offsetInDescription = *(u32 *)(Data + 38);
        u8 AtBegin = *(u8 *)(Data + 42);

        gf_isom_hint_sample_description_data(isom_file, trackNumber, SourceTrackID, sampleDescriptionIndex,
                                             DataLength, offsetInDescription, AtBegin);
    }

    const u32 *brands = gf_isom_get_brands(isom_file);

    if (Size >= 55) {
        u32 average_bitrate = *(u32 *)(Data + 43);
        u32 max_bitrate = *(u32 *)(Data + 47);
        u32 decode_buffer_size = *(u32 *)(Data + 51);

        gf_isom_update_bitrate(isom_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);
    }

    u8 *output = NULL;
    u32 output_size = 0;

    gf_isom_get_stsd_template(isom_file, trackNumber, sampleDescriptionIndex, &output, &output_size);
    if (output) {
        free(output);
    }

    u8 *out_dsi = NULL;
    u32 out_size = 0;

    gf_isom_get_jp2_config(isom_file, trackNumber, sampleDescriptionIndex, &out_dsi, &out_size);
    if (out_dsi) {
        free(out_dsi);
    }

    cleanup_iso_file(isom_file);
    return 0;
}