// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_max_sample_delta at isom_read.c:2043:5 in isomedia.h
// gf_isom_get_meta_item_flags at meta.c:207:5 in isomedia.h
// gf_isom_has_segment at isom_read.c:843:6 in isomedia.h
// gf_isom_get_track_by_id at isom_read.c:807:5 in isomedia.h
// gf_isom_get_fragments_count at isom_read.c:5418:5 in isomedia.h
// gf_isom_enum_track_group at isom_read.c:6457:6 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) {
        return 0;
    }

    prepare_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = Data[0];
    u32 trackID = Data[1];
    u32 item_num = Data[2];
    Bool root_meta = Data[3] % 2;
    Bool segments_only = Data[4] % 2;
    u32 idx = 0;
    u32 track_group_type;
    u32 track_group_id;
    u32 brand;
    u32 version;

    // Fuzz gf_isom_get_max_sample_delta
    u32 max_sample_delta = gf_isom_get_max_sample_delta(isom_file, trackNumber);

    // Fuzz gf_isom_get_meta_item_flags
    u32 meta_item_flags = gf_isom_get_meta_item_flags(isom_file, root_meta, trackNumber, item_num);

    // Fuzz gf_isom_has_segment
    Bool has_segment = gf_isom_has_segment(isom_file, &brand, &version);

    // Fuzz gf_isom_get_track_by_id
    u32 track_by_id = gf_isom_get_track_by_id(isom_file, trackID);

    // Fuzz gf_isom_get_fragments_count
    u32 fragments_count = gf_isom_get_fragments_count(isom_file, segments_only);

    // Fuzz gf_isom_enum_track_group
    Bool enum_track_group = gf_isom_enum_track_group(isom_file, trackNumber, &idx, &track_group_type, &track_group_id);

    gf_isom_close(isom_file);

    // Return value is ignored by fuzzer
    return 0;
}