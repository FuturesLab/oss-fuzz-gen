#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Initialize variables
    const char *fileName = NULL; // NULL for in-memory operation
    GF_ISOOpenMode openMode = GF_ISOM_OPEN_READ; // Example open mode
    const char *tmp_dir = "/tmp"; // Example temporary directory

    GF_ISOFile *file = gf_isom_open(fileName, openMode, tmp_dir);
    if (!file) return 0;

    Bool root_meta = GF_FALSE;
    u32 track_num = 1;
    const char *item_name = "test_item";
    u32 item_id = 0;
    u32 item_type = 1; // Example item type
    const char *mime_type = "image/jpeg";
    const char *content_encoding = "identity";
    GF_ImageItemProperties image_props = {0};
    char *data_copy = (char *)malloc(size);
    if (!data_copy) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(data_copy, data, size);
    u32 data_len = size;
    GF_List *item_extent_refs = gf_list_new();

    // Call the function-under-test
    gf_isom_add_meta_item_memory(file, root_meta, track_num, item_name, &item_id, item_type, mime_type, content_encoding, &image_props, data_copy, data_len, item_extent_refs);

    // Clean up
    free(data_copy);
    gf_list_del(item_extent_refs);
    gf_isom_close(file);

    return 0;
}