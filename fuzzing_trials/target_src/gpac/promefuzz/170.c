// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_y3d_info at isom_read.c:6244:8 in isomedia.h
// gf_isom_remove_sample_group at isom_write.c:7632:8 in isomedia.h
// gf_isom_mvc_config_del at avc_ext.c:1823:8 in isomedia.h
// gf_isom_set_y3d_info at isom_write.c:9065:8 in isomedia.h
// gf_isom_set_sample_cenc_default_group at isom_write.c:7843:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_170(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *(((u32 *)Data) + 1);
    u32 grouping_type = *(((u32 *)Data) + 2);

    GF_ISOM_Y3D_Info info;
    GF_Err err;

    // Test gf_isom_get_y3d_info
    err = gf_isom_get_y3d_info(isom_file, trackNumber, sampleDescriptionIndex, &info);

    // Test gf_isom_remove_sample_group
    err = gf_isom_remove_sample_group(isom_file, trackNumber, grouping_type);

    // Test gf_isom_mvc_config_del
    err = gf_isom_mvc_config_del(isom_file, trackNumber, sampleDescriptionIndex);

    // Test gf_isom_set_y3d_info
    err = gf_isom_set_y3d_info(isom_file, trackNumber, sampleDescriptionIndex, &info);

    // Test gf_isom_set_sample_cenc_default_group
    err = gf_isom_set_sample_cenc_default_group(isom_file, trackNumber, sampleDescriptionIndex);

    // Test gf_isom_set_track_id
    err = gf_isom_set_track_id(isom_file, trackNumber, grouping_type);

    gf_isom_close(isom_file);

    return 0;
}