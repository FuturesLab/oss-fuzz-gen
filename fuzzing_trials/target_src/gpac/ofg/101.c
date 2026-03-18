#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) return 0; // Exit if file creation fails

    Bool root_meta = 1; // True
    u32 track_num = 1; // Arbitrary track number
    Bool self_reference = 0; // False

    char resource_path[256];
    char item_name[256];
    const char *mime_type = "video/mp4";
    const char *content_encoding = "identity";
    const char *URL = "http://example.com";
    const char *URN = "urn:example";
    u32 io_item_id = 0;
    u32 item_type = 1; // Arbitrary item type
    GF_ImageItemProperties image_props;

    // Ensure the data is not too large for our buffers
    if (size > 255) size = 255;

    // Copy data into resource_path and item_name
    memcpy(resource_path, data, size);
    resource_path[size] = '\0'; // Null-terminate
    memcpy(item_name, data, size);
    item_name[size] = '\0'; // Null-terminate

    // Initialize image properties
    memset(&image_props, 0, sizeof(GF_ImageItemProperties));

    // Call the function under test
    gf_isom_add_meta_item2(file, root_meta, track_num, self_reference, resource_path, item_name, &io_item_id, item_type,
                           mime_type, content_encoding, URL, URN, &image_props);

    // Clean up
    gf_isom_close(file);

    return 0;
}