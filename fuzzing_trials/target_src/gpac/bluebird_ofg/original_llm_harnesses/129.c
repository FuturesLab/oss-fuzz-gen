#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/list.h> // Include necessary for GF_List

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Initialize GF_ISOFile using the appropriate library function
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);

    if (!file) return 0;

    Bool root_meta = GF_TRUE; // or GF_FALSE, try both
    u32 track_num = 1; // Example track number
    u32 item_id = 1; // Example item ID
    GF_ImageItemProperties prop;
    GF_List *unmapped_props = gf_list_new();

    // Call the function-under-test
    gf_isom_get_meta_image_props(file, root_meta, track_num, item_id, &prop, unmapped_props);

    // Clean up
    gf_isom_close(file); // Properly close the initialized file
    gf_list_del(unmapped_props);

    return 0;
}