#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For mkstemp, write, close, remove
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize trackNumber to a non-zero value

    // Create a temporary ISO file from the input data
    if (size > 0) {
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            write(fd, data, size);
            close(fd);

            // Open the ISO file
            movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
            if (movie != NULL) {
                // Call the function-under-test
                gf_isom_remove_edits(movie, trackNumber);

                // Close the movie
                gf_isom_close(movie);
            }

            // Remove the temporary file
            remove(tmpl);
        }
    }

    return 0;
}