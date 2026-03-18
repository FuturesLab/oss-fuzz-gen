#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read necessary parameters
    if (size < sizeof(u32) * 4 + sizeof(Bool)) {
        return 0;
    }

    // Create a temporary file to simulate file input for gf_isom_open
    char tmp_filename[] = "/tmp/fuzz_input.XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }
    
    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmp_filename);
        return 0;
    }
    close(fd);

    // Initialize the GF_ISOFile structure using the temporary file
    GF_ISOFile *file = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        unlink(tmp_filename);
        return 0;
    }

    // Extract parameters from data
    size_t offset = 0;
    Bool root_meta = (Bool)data[offset];
    offset += sizeof(Bool);

    u32 track_num = *(u32 *)(data + offset);
    offset += sizeof(u32);

    u32 item_num = *(u32 *)(data + offset);
    offset += sizeof(u32);

    // Initialize output parameters
    u32 itemID = 0;
    u32 type = 0;
    u32 protection_scheme = 0;
    u32 protection_scheme_version = 0;
    Bool is_self_reference = false;
    const char *item_name = NULL;
    const char *item_mime_type = NULL;
    const char *item_encoding = NULL;
    const char *item_url = NULL;
    const char *item_urn = NULL;

    // Call the function-under-test
    gf_isom_get_meta_item_info(file, root_meta, track_num, item_num, &itemID, &type, &protection_scheme, &protection_scheme_version, &is_self_reference, &item_name, &item_mime_type, &item_encoding, &item_url, &item_urn);

    // Clean up
    gf_isom_close(file);
    unlink(tmp_filename);

    return 0;
}