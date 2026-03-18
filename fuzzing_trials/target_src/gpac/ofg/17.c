#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // For close()
#include <fcntl.h>  // For mkstemp()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    u32 from_id = 1;
    u32 type = 1;
    u32 ref_idx = 1;

    // Ensure the data size is large enough to simulate a file
    if (size > 0) {
        // Create a temporary file to simulate the GF_ISOFile
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            write(fd, data, size);
            close(fd);

            // Open the ISO file using the temporary file
            file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
        }
    }

    // Fuzz the function with the initialized parameters
    if (file != NULL) {
        gf_isom_meta_get_item_ref_id(file, root_meta, track_num, from_id, type, ref_idx);
        gf_isom_close(file);
    }

    return 0;
}