// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_y3d_info at isom_write.c:9065:8 in isomedia.h
// gf_isom_evte_config_new at sample_descs.c:1846:8 in isomedia.h
// gf_isom_set_nalu_length_field at isom_write.c:8502:8 in isomedia.h
// gf_isom_mvc_config_del at avc_ext.c:1823:8 in isomedia.h
// gf_isom_update_bitrate at sample_descs.c:1776:8 in isomedia.h
// gf_isom_get_y3d_info at isom_read.c:6244:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_179(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(GF_ISOM_Y3D_Info) + sizeof(u32) * 3) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    GF_ISOM_Y3D_Info *info = (GF_ISOM_Y3D_Info *)(Data + sizeof(u32) * 2);

    // Fuzz gf_isom_set_y3d_info
    gf_isom_set_y3d_info(isom_file, trackNumber, sampleDescriptionIndex, info);

    // Fuzz gf_isom_evte_config_new
    u32 outDescriptionIndex;
    gf_isom_evte_config_new(isom_file, trackNumber, &outDescriptionIndex);

    // Fuzz gf_isom_set_nalu_length_field
    u32 nalu_size_length = *(u32 *)(Data + sizeof(u32) * 3);
    gf_isom_set_nalu_length_field(isom_file, trackNumber, sampleDescriptionIndex, nalu_size_length);

    // Fuzz gf_isom_mvc_config_del
    gf_isom_mvc_config_del(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_update_bitrate
    u32 average_bitrate = *(u32 *)(Data + sizeof(u32) * 4);
    u32 max_bitrate = *(u32 *)(Data + sizeof(u32) * 5);
    u32 decode_buffer_size = *(u32 *)(Data + sizeof(u32) * 6);
    gf_isom_update_bitrate(isom_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);

    // Fuzz gf_isom_get_y3d_info
    GF_ISOM_Y3D_Info retrieved_info;
    gf_isom_get_y3d_info(isom_file, trackNumber, sampleDescriptionIndex, &retrieved_info);

    gf_isom_close(isom_file);
    return 0;
}