#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() and write()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Assuming non-zero for true
    u32 track_num = 1;  // Arbitrary non-zero track number
    u32 item_id = 1;    // Arbitrary non-zero item ID
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0; // Failed to create temp file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0; // Failed to write all data
    }

    // Close the file descriptor as we only need the filename
    close(fd);

    // Call the function under test
    gf_isom_extract_meta_item(file, root_meta, track_num, item_id, tmpl);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}