#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For close() and unlink()

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    GF_ISOFile *file;
    Bool root_meta = 1;
    u32 track_num = 1;
    Bool self_reference = 0;
    char resource_path[] = "/tmp/resource";
    char item_name[] = "item_name";
    u32 item_id = 1;
    u32 item_type = 1;
    char mime_type[] = "application/octet-stream";
    char content_encoding[] = "identity";
    char URL[] = "http://example.com";
    char URN[] = "urn:example";
    GF_ImageItemProperties image_props;

    // Initialize GF_ImageItemProperties with some default values
    memset(&image_props, 0, sizeof(GF_ImageItemProperties));

    // Create a temporary file to simulate GF_ISOFile
    char tmpl[] = "/tmp/gf_isofileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Open the temporary file as a GF_ISOFile
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_add_meta_item(file, root_meta, track_num, self_reference, resource_path, item_name, item_id, item_type, mime_type, content_encoding, URL, URN, &image_props);

    // Close the GF_ISOFile
    gf_isom_close(file);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}