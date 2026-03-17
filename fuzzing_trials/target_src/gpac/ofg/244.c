#include <gpac/isomedia.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) return 0;

    Bool root_meta = GF_TRUE; // or GF_FALSE, try both
    u32 meta_track_number = 1; // Example track number
    char item_name[256]; // Buffer for item name
    u32 item_id = 1; // Example item ID
    GF_ImageItemProperties image_props; // Image properties

    // Initialize item_name with data
    size_t name_length = size < 255 ? size : 255;
    memcpy(item_name, data, name_length);
    item_name[name_length] = '\0'; // Null-terminate the string

    // Initialize image_props with some default values
    image_props.width = 1920;
    image_props.height = 1080;
    image_props.depth = 24;
    // Remove the line setting image_props.color_type as it does not exist

    // Call the function-under-test
    gf_isom_iff_create_image_overlay_item(movie, root_meta, meta_track_number, item_name, item_id, &image_props);

    // Clean up
    gf_isom_close(movie);

    return 0;
}