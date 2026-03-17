#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Initialize to a non-zero value (true)
    u32 track_num = 1;  // Initialize to a valid track number
    u32 item_ID = 1;    // Initialize to a valid item ID

    // Create a temporary file name for the ISO media file
    char temp_filename[] = "/tmp/fuzz_isomedia_XXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Attempt to open the ISO media file using the temporary file name
    file = gf_isom_open(temp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        unlink(temp_filename);
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_meta_item_by_id(file, root_meta, track_num, item_ID);

    // Close the file and clean up
    gf_isom_close(file);
    unlink(temp_filename);

    return 0;
}