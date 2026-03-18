#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0; // Exit if movie creation failed
    }

    GF_ISOTrackID trackID = 1; // Assuming track ID 1 for testing
    u32 is_leading = size > 0 ? data[0] : 0;
    u32 dependsOn = size > 1 ? data[1] : 0;
    u32 dependedOn = size > 2 ? data[2] : 0;
    u32 redundant = size > 3 ? data[3] : 0;

    // Call the function-under-test
    gf_isom_fragment_set_sample_flags(movie, trackID, is_leading, dependsOn, dependedOn, redundant);

    // Clean up
    gf_isom_close(movie);

    return 0;
}