#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/internal/isomedia_dev.h>

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize parameters for gf_isom_iff_create_image_grid_item
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Return early if movie cannot be opened
    }
    Bool root_meta = GF_TRUE;
    u32 meta_track_number = 1;
    const char *item_name = "test_item";
    u32 item_id = 1;
    
    GF_ImageItemProperties image_props;
    image_props.width = 100;
    image_props.height = 100;

    // Removed non-existent fields 'flags' and 'reserved'

    // Call the function-under-test
    gf_isom_iff_create_image_grid_item(movie, root_meta, meta_track_number, item_name, item_id, &image_props);

    // Clean up
    gf_isom_close(movie);

    return 0;
}