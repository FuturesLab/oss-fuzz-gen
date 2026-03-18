#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for mkstemp and close

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // A non-zero value for true
    u32 track_num = 1;  // Example track number
    char outName[] = "/tmp/output.xml"; // Output file name
    Bool is_binary = 0; // Assuming XML output is not binary

    // Ensure data is not empty and create a temporary file for the input
    if (size > 0) {
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            write(fd, data, size);
            close(fd);

            // Open the ISO file from the temporary file
            file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
            if (file != NULL) {
                // Call the function-under-test
                gf_isom_extract_meta_xml(file, root_meta, track_num, outName, &is_binary);

                // Close the ISO file
                gf_isom_close(file);
            }

            // Remove the temporary file
            remove(tmpl);
        }
    }

    return 0;
}