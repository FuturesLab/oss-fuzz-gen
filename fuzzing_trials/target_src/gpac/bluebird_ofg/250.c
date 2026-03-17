#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) return 0;

    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    const char *item_name = "test_item";
    u32 item_id = 0;
    u32 item_type = 1;
    const char *mime_type = "video/mp4";
    const char *content_encoding = "identity";
    GF_ImageItemProperties image_props = {0};
    u32 tk_id = 1;
    u32 sample_num = 1;

    // Call the function-under-test
    gf_isom_add_meta_item_sample_ref(file, root_meta, track_num, item_name, &item_id, item_type, mime_type, content_encoding, &image_props, tk_id, sample_num);

    // Clean up
    gf_isom_close(file);

    return 0;
}