// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_nalu_length_field at isom_write.c:8502:8 in isomedia.h
// gf_isom_cenc_allocate_storage at drm_sample.c:1142:8 in isomedia.h
// gf_isom_ac3_config_update at sample_descs.c:746:8 in isomedia.h
// gf_isom_rtp_set_time_sequence_offset at hint_track.c:292:8 in isomedia.h
// gf_isom_get_alternate_brand at isom_read.c:2648:8 in isomedia.h
// gf_isom_svc_config_del at avc_ext.c:1818:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for the dummy ISO file and initialize it
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *(((u32 *)Data) + 1);
    u32 nalu_size_length = *(((u32 *)Data) + 2);
    u32 SequenceNumberOffset = *(((u32 *)Data) + 3);
    u32 BrandIndex = *(((u32 *)Data) + 4);

    GF_AC3Config ac3_config;
    ac3_config.nb_streams = Data[0] % 8;
    ac3_config.sample_rate = *((u32 *)(Data + 1)) % 48000;
    ac3_config.framesize = *((u32 *)(Data + 5)) % 2048;

    u32 brand;
    
    gf_isom_set_nalu_length_field(iso_file, trackNumber, sampleDescriptionIndex, nalu_size_length);
    gf_isom_cenc_allocate_storage(iso_file, trackNumber);
    gf_isom_ac3_config_update(iso_file, trackNumber, sampleDescriptionIndex, &ac3_config);
    gf_isom_rtp_set_time_sequence_offset(iso_file, trackNumber, sampleDescriptionIndex, SequenceNumberOffset);
    gf_isom_get_alternate_brand(iso_file, BrandIndex, &brand);
    gf_isom_svc_config_del(iso_file, trackNumber, sampleDescriptionIndex);

    gf_isom_close(iso_file);
    return 0;
}