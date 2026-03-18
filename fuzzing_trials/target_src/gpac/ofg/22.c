#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and write()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    u32 item_id = 1;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Call the function-under-test
    gf_isom_extract_meta_item(file, root_meta, track_num, item_id, tmpl);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}