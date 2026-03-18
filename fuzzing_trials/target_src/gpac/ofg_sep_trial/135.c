#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmp_filename[] = "/tmp/fuzz_input_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmp_filename);
        return 0;
    }

    // Close the file descriptor as we will open it again in read mode
    close(fd);

    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    u32 media_segment_type = GF_ISOM_BRAND_ISOM;
    Bool mvex_after_tracks = GF_FALSE;

    // Check if the movie was successfully opened
    if (movie == NULL) {
        unlink(tmp_filename);
        return 0;
    }

    // Call the function-under-test
    gf_isom_finalize_for_fragment(movie, media_segment_type, mvex_after_tracks);

    // Clean up
    gf_isom_close(movie);
    unlink(tmp_filename);

    return 0;
}