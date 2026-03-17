#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

// The LLVMFuzzerTestOneInput function is the entry point for the fuzzer.
int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Check if size is sufficient to create a file and read metadata
    if (size < 1) return 0;

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the file using GF_ISOFile
    GF_ISOFile *file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        remove(tmpl);
        return 0;
    }

    // Initialize variables for the function call
    Bool root_meta = true;
    u32 track_num = 1;
    u32 item_num = 1;
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

    // Close the file and remove the temporary file
    gf_isom_close(file);
    remove(tmpl);

    return 0;
}