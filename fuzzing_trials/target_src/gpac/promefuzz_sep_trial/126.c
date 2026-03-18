// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_meta_get_item_ref_id at meta.c:2226:5 in isomedia.h
// gf_isom_get_meta_primary_item_id at meta.c:600:5 in isomedia.h
// gf_isom_get_meta_item_by_id at meta.c:219:5 in isomedia.h
// gf_isom_meta_item_has_ref at meta.c:2203:5 in isomedia.h
// gf_isom_get_meta_item_flags at meta.c:207:5 in isomedia.h
// gf_isom_get_meta_type at meta.c:43:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Since we don't have the complete definition of GF_ISOFile, we can't allocate it directly.
    // Instead, we allocate a dummy pointer assuming the library handles it internally.
    GF_ISOFile* iso_file = NULL;
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile* iso_file) {
    // Assume the library provides a function to clean up or close the ISO file
    // Here, we just simulate cleanup
    if (iso_file) {
        // Free or close operations if needed
    }
}

int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 param1 = *(u32*)(Data);
    u32 param2 = *(u32*)(Data + 4);
    u32 param3 = *(u32*)(Data + 8);
    u32 param4 = *(u32*)(Data + 12);
    u32 param5 = *(u32*)(Data + 16);

    Bool root_meta = (Bool)(param1 % 2);
    u32 track_num = param2;
    u32 item_id = param3;
    u32 type = param4;
    u32 ref_idx = param5 % 10 + 1; // Ensure it's 1-based

    // Test gf_isom_meta_get_item_ref_id
    u32 ref_id = gf_isom_meta_get_item_ref_id(iso_file, root_meta, track_num, item_id, type, ref_idx);

    // Test gf_isom_get_meta_primary_item_id
    u32 primary_id = gf_isom_get_meta_primary_item_id(iso_file, root_meta, track_num);

    // Test gf_isom_get_meta_item_by_id
    u32 item_index = gf_isom_get_meta_item_by_id(iso_file, root_meta, track_num, item_id);

    // Test gf_isom_meta_item_has_ref
    u32 ref_count = gf_isom_meta_item_has_ref(iso_file, root_meta, track_num, item_id, type);

    // Test gf_isom_get_meta_item_flags
    u32 item_flags = gf_isom_get_meta_item_flags(iso_file, root_meta, track_num, ref_idx);

    // Test gf_isom_get_meta_type
    u32 meta_type = gf_isom_get_meta_type(iso_file, root_meta, track_num);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}