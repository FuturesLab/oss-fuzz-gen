#include <stdint.h>
#include <stddef.h>
#include "/src/gpac/include/gpac/isomedia.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to be a valid input
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to hold the input data
    char tmpFileName[] = "/tmp/fuzz_input_XXXXXX";
    int fd = mkstemp(tmpFileName);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpFileName);
        return 0;
    }
    close(fd);

    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(tmpFileName, GF_ISOM_OPEN_READ, NULL);
    u32 trackNumber = 1;  // Set a non-zero track number
    Bool remove = GF_FALSE;  // Set remove to GF_FALSE

    // Ensure the movie is not NULL before calling the function
    if (movie != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_update_aperture_info with gf_isom_reset_track_switch_parameter
        gf_isom_reset_track_switch_parameter(movie, trackNumber, remove);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Close the movie to clean up resources

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_sdp_clean
        gf_isom_sdp_clean(movie);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Clean up the temporary file
    unlink(tmpFileName);

    return 0;
}