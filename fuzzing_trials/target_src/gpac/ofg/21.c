#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // For close() and unlink()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Non-zero value for true
    u32 track_num = 1; // Example track number
    u32 item_id = 1; // Example item ID

    // Create a temporary file for dump_file_name
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Initialize the GF_ISOFile structure
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_extract_meta_item(file, root_meta, track_num, item_id, tmpl);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}