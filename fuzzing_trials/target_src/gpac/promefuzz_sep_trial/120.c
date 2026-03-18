// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_meta_get_item_ref_id at meta.c:2226:5 in isomedia.h
// gf_isom_get_meta_item_count at meta.c:123:5 in isomedia.h
// gf_isom_get_meta_primary_item_id at meta.c:600:5 in isomedia.h
// gf_isom_meta_item_has_ref at meta.c:2203:5 in isomedia.h
// gf_isom_get_meta_item_by_id at meta.c:219:5 in isomedia.h
// gf_isom_get_meta_item_flags at meta.c:207:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) return 0;

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!iso_file) return 0;

    u32 track_num = *(u32*)(Data);
    u32 from_id = *(u32*)(Data + sizeof(u32));
    u32 type = *(u32*)(Data + 2 * sizeof(u32));
    u32 ref_idx = *(u32*)(Data + 3 * sizeof(u32));
    u32 item_ID = *(u32*)(Data + 4 * sizeof(u32));

    Bool root_meta = (Size > 5 * sizeof(u32)) ? (Bool)Data[5 * sizeof(u32)] : GF_FALSE;

    // Call target functions with diverse parameters
    u32 ref_id = gf_isom_meta_get_item_ref_id(iso_file, root_meta, track_num, from_id, type, ref_idx);
    u32 meta_item_count = gf_isom_get_meta_item_count(iso_file, root_meta, track_num);
    u32 primary_item_id = gf_isom_get_meta_primary_item_id(iso_file, root_meta, track_num);
    u32 item_has_ref = gf_isom_meta_item_has_ref(iso_file, root_meta, track_num, from_id, type);
    u32 item_by_id = gf_isom_get_meta_item_by_id(iso_file, root_meta, track_num, item_ID);
    u32 item_flags = gf_isom_get_meta_item_flags(iso_file, root_meta, track_num, ref_idx);

    // Use the return values to prevent compiler optimizations
    (void)ref_id;
    (void)meta_item_count;
    (void)primary_item_id;
    (void)item_has_ref;
    (void)item_by_id;
    (void)item_flags;

    gf_isom_close(iso_file);
    return 0;
}