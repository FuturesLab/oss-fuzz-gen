#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    Bool root_meta = 1;
    u32 track_num = 1;
    Bool self_reference = 0;

    // Create a temporary file to use as resource_path
    char resource_path[] = "/tmp/resourceXXXXXX";
    int fd = mkstemp(resource_path);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    char item_name[] = "item_name";
    u32 io_item_id = 0;
    u32 item_type = 0;

    char mime_type[] = "video/mp4";
    char content_encoding[] = "identity";
    char URL[] = "http://example.com";
    char URN[] = "urn:example";

    GF_ImageItemProperties image_props;
    memset(&image_props, 0, sizeof(GF_ImageItemProperties));

    // Call the function-under-test
    gf_isom_add_meta_item2(file, root_meta, track_num, self_reference, resource_path, item_name, &io_item_id, item_type,
                           mime_type, content_encoding, URL, URN, &image_props);

    // Clean up
    gf_isom_close(file);
    unlink(resource_path);

    return 0;
}