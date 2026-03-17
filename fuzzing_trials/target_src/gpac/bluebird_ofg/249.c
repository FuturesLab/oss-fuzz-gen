#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    Bool root_meta = 1; // Assuming true for root_meta
    u32 track_num = 1; // Assuming a valid track number
    const char *item_name = "test_item";
    u32 item_id = 0; // Initialize item_id
    u32 item_type = 1; // Assuming a valid item type
    const char *mime_type = "application/octet-stream";
    const char *content_encoding = "identity";

    GF_ImageItemProperties image_props;
    memset(&image_props, 0, sizeof(GF_ImageItemProperties)); // Zero-initialize

    char *data_copy = (char *)malloc(size);
    if (data_copy == NULL) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(data_copy, data, size);

    GF_List *item_extent_refs = gf_list_new();
    if (item_extent_refs == NULL) {
        free(data_copy);
        gf_isom_close(file);
        return 0;
    }

    gf_isom_add_meta_item_memory(file, root_meta, track_num, item_name, &item_id, item_type, mime_type, content_encoding, &image_props, data_copy, (u32)size, item_extent_refs);

    gf_list_del(item_extent_refs);
    free(data_copy);
    gf_isom_close(file);

    return 0;
}