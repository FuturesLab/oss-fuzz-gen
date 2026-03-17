// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_meta_type at meta.c:43:5 in isomedia.h
// gf_isom_has_meta_xml at meta.c:52:5 in isomedia.h
// gf_isom_get_meta_item_count at meta.c:123:5 in isomedia.h
// gf_isom_get_meta_primary_item_id at meta.c:600:5 in isomedia.h
// gf_isom_meta_get_item_ref_id at meta.c:2226:5 in isomedia.h
// gf_isom_meta_get_item_ref_count at meta.c:2185:5 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    // Allocate a dummy ISO file structure
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = initialize_iso_file();
    if (!iso_file) return 0;

    // Extract parameters from Data
    Bool root_meta = Data[0] % 2; // Randomly choose true/false
    u32 track_num = (Size > 1) ? Data[1] : 0; // Use second byte for track number if available

    // Test gf_isom_get_meta_type
    u32 meta_type = gf_isom_get_meta_type(iso_file, root_meta, track_num);
    
    // Test gf_isom_has_meta_xml
    u32 has_meta_xml = gf_isom_has_meta_xml(iso_file, root_meta, track_num);

    // Test gf_isom_get_meta_item_count
    u32 meta_item_count = gf_isom_get_meta_item_count(iso_file, root_meta, track_num);

    // Test gf_isom_get_meta_primary_item_id
    u32 primary_item_id = gf_isom_get_meta_primary_item_id(iso_file, root_meta, track_num);

    // Test gf_isom_meta_get_item_ref_id
    u32 from_id = (Size > 2) ? Data[2] : 0;
    u32 type = (Size > 3) ? Data[3] : 0;
    u32 ref_idx = (Size > 4) ? Data[4] : 0;
    u32 ref_id = gf_isom_meta_get_item_ref_id(iso_file, root_meta, track_num, from_id, type, ref_idx);

    // Test gf_isom_meta_get_item_ref_count
    u32 ref_count = gf_isom_meta_get_item_ref_count(iso_file, root_meta, track_num, from_id, type);

    // Clean up
    cleanup_iso_file(iso_file);

    return 0;
}