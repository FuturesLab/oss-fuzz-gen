#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and write()
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_231(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *file;
    Bool root_meta = 1; // Non-zero value for true
    u32 track_num = 1;  // Example track number
    u32 item_num = 1;   // Example item number

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Exit if file creation fails
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the ISO media file
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        remove(tmpl); // Clean up the temporary file
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_meta_item_flags(file, root_meta, track_num, item_num);

    // Clean up
    gf_isom_close(file);
    remove(tmpl);

    return 0;
}