// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_iff_create_image_identity_item at iff.c:2107:8 in isomedia.h
// gf_isom_get_meta_image_props at meta.c:735:8 in isomedia.h
// gf_isom_iff_create_image_item_from_track at iff.c:2118:8 in isomedia.h
// gf_isom_add_meta_item_memory at meta.c:1800:8 in isomedia.h
// gf_isom_iff_create_image_overlay_item at iff.c:2063:8 in isomedia.h
// gf_isom_iff_create_image_grid_item at iff.c:1929:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void initialize_image_properties(GF_ImageItemProperties *image_props) {
    // Initialize the GF_ImageItemProperties structure with dummy values
    memset(image_props, 0, sizeof(GF_ImageItemProperties));
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    // Create a dummy ISO file pointer
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    Bool root_meta = GF_TRUE;
    u32 meta_track_number = 0;
    const char *item_name = "dummy_item";
    u32 item_id = 0;
    GF_ImageItemProperties image_props;
    initialize_image_properties(&image_props);

    // Fuzz gf_isom_iff_create_image_identity_item
    gf_isom_iff_create_image_identity_item(isom_file, root_meta, meta_track_number, item_name, item_id, &image_props);

    // Fuzz gf_isom_get_meta_image_props
    GF_List *unmapped_props = gf_list_new();
    gf_isom_get_meta_image_props(isom_file, root_meta, meta_track_number, item_id, &image_props, unmapped_props);

    // Fuzz gf_isom_iff_create_image_item_from_track
    u32 media_track = 1;
    GF_List *item_extent_refs = gf_list_new();
    gf_isom_iff_create_image_item_from_track(isom_file, root_meta, meta_track_number, media_track, item_name, item_id, &image_props, item_extent_refs);

    // Fuzz gf_isom_add_meta_item_memory
    u32 item_type = 0;
    const char *mime_type = "image/jpeg";
    const char *content_encoding = "identity";
    char *data = (char *)Data;
    u32 data_len = (u32)Size;
    gf_isom_add_meta_item_memory(isom_file, root_meta, meta_track_number, item_name, &item_id, item_type, mime_type, content_encoding, &image_props, data, data_len, item_extent_refs);

    // Fuzz gf_isom_iff_create_image_overlay_item
    gf_isom_iff_create_image_overlay_item(isom_file, root_meta, meta_track_number, item_name, item_id, &image_props);

    // Fuzz gf_isom_iff_create_image_grid_item
    gf_isom_iff_create_image_grid_item(isom_file, root_meta, meta_track_number, item_name, item_id, &image_props);

    // Cleanup
    gf_list_del(unmapped_props);
    gf_list_del(item_extent_refs);
    gf_isom_close(isom_file);

    return 0;
}