// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_udta_type at isom_read.c:2711:8 in isomedia.h
// gf_isom_set_sample_cenc_default_group at isom_write.c:7843:8 in isomedia.h
// gf_isom_remove_cenc_senc_box at drm_sample.c:996:8 in isomedia.h
// gf_isom_remove_sample_group at isom_write.c:7632:8 in isomedia.h
// gf_isom_remove_track_references at isom_write.c:5036:8 in isomedia.h
// gf_isom_set_ipod_compatible at isom_write.c:8995:8 in isomedia.h
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

int LLVMFuzzerTestOneInput_297(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(const u32 *)Data;
    u32 udta_idx = *(const u32 *)(Data + sizeof(u32));
    u32 sampleNumber = *(const u32 *)(Data + 2 * sizeof(u32));
    u32 grouping_type = *(const u32 *)(Data + 3 * sizeof(u32));

    u32 UserDataType;
    bin128 UUID;

    gf_isom_get_udta_type(isom_file, trackNumber, udta_idx, &UserDataType, UUID);
    gf_isom_set_sample_cenc_default_group(isom_file, trackNumber, sampleNumber);
    gf_isom_remove_cenc_senc_box(isom_file, trackNumber);
    gf_isom_remove_sample_group(isom_file, trackNumber, grouping_type);
    gf_isom_remove_track_references(isom_file, trackNumber);
    gf_isom_set_ipod_compatible(isom_file, trackNumber);

    gf_isom_close(isom_file);

    return 0;
}