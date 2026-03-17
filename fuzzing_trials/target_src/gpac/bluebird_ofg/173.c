#include <stdint.h>
#include <stddef.h>
#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *file = NULL;
    u32 track = 1;  // Initialize track with a non-zero value

    // Check if the size is sufficient to create a valid ISO file
    if (size > 0) {
        // Create a temporary file to store the input data
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            // Write data to the temporary file
            write(fd, data, size);
            close(fd);

            // Open the file as an ISO file
            file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
            if (file != NULL) {
                // Call the function-under-test

                // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_find_od_id_for_track with gf_isom_get_edits_count
                gf_isom_get_edits_count(file, track);
                // End mutation: Producer.REPLACE_FUNC_MUTATOR



                // Close the ISO file
                gf_isom_close(file);
            }

            // Remove the temporary file
            unlink(tmpl);
        }    }

    return 0;
}