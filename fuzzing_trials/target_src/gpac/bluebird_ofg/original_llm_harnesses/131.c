#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <unistd.h>   // For close() and write()
#include <stdlib.h>   // For mkstemp()
#include <stdio.h>    // For remove()

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Initialize with a non-zero value (true)
    u32 track_num = 1;  // Initialize with a non-zero value

    // Check if the data size is sufficient to open a file
    if (size > 0) {
        // Create a temporary file to simulate the input file
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            // Write data to the temporary file
            write(fd, data, size);
            close(fd);

            // Open the ISO file using the temporary file path
            file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
            if (file != NULL) {
                // Call the function-under-test
                gf_isom_get_meta_type(file, root_meta, track_num);

                // Close the file after testing
                gf_isom_close(file);
            }

            // Remove the temporary file
            remove(tmpl);
        }
    }

    return 0;
}

#ifdef __cplusplus
}
#endif