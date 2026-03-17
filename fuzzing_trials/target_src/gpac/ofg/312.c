#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gpac/isomedia.h"  // Include the correct header for GF_ISOFile and related types

int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) return 0;

    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    Bool self_reference = GF_FALSE;

    // Ensure the resource path is null-terminated and non-NULL
    char resource_path[256];
    snprintf(resource_path, sizeof(resource_path), "resource_path_%.*s", (int)size, data);

    // Ensure the item name is null-terminated and non-NULL
    char item_name[256];
    snprintf(item_name, sizeof(item_name), "item_name_%.*s", (int)size, data);

    u32 item_id = 1;
    u32 item_type = 1;

    // Ensure the mime type is null-terminated and non-NULL
    char mime_type[256];
    snprintf(mime_type, sizeof(mime_type), "mime/type_%.*s", (int)size, data);

    // Ensure the content encoding is null-terminated and non-NULL
    char content_encoding[256];
    snprintf(content_encoding, sizeof(content_encoding), "encoding_%.*s", (int)size, data);

    // Ensure the URL is null-terminated and non-NULL
    char URL[256];
    snprintf(URL, sizeof(URL), "http://example.com/%.*s", (int)size, data);

    // Ensure the URN is null-terminated and non-NULL
    char URN[256];
    snprintf(URN, sizeof(URN), "urn:example:%.*s", (int)size, data);

    GF_ImageItemProperties image_props;
    memset(&image_props, 0, sizeof(GF_ImageItemProperties));

    // Call the function-under-test
    gf_isom_add_meta_item(file, root_meta, track_num, self_reference, resource_path, item_name, item_id, item_type, mime_type, content_encoding, URL, URN, &image_props);

    // Clean up
    gf_isom_close(file);

    return 0;
}