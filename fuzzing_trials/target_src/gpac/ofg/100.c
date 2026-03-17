#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/internal/isomedia_dev.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract necessary parameters
    if (size < sizeof(u32) + sizeof(Bool) + 1) {
        return 0;
    }

    // Initialize the parameters for gf_isom_iff_create_image_grid_item
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from data
    Bool root_meta = (Bool)data[0];
    u32 meta_track_number = *((u32 *)(data + 1));

    // Ensure item_name is a null-terminated string
    const char *item_name = (const char *)(data + 1 + sizeof(u32));
    size_t item_name_length = strnlen(item_name, size - 1 - sizeof(u32));
    if (item_name_length == 0 || item_name_length >= size - 1 - sizeof(u32)) {
        gf_isom_close(movie);
        return 0;
    }

    u32 item_id = 1;  // Set a non-zero item_id
    GF_ImageItemProperties image_props;
    memset(&image_props, 0, sizeof(GF_ImageItemProperties));

    // Call the function-under-test
    gf_isom_iff_create_image_grid_item(movie, root_meta, meta_track_number, item_name, item_id, &image_props);

    // Clean up
    gf_isom_close(movie);

    return 0;
}