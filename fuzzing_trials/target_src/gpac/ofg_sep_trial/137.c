#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>  // Include the necessary header for GPAC ISO media handling

extern int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    GF_ISOTrackID trackID = 1; // Using a non-zero track ID
    u32 is_leading = 0;
    u32 dependsOn = 1;
    u32 dependedOn = 1;
    u32 redundant = 0;

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    GF_Err result = gf_isom_fragment_set_sample_flags(movie, trackID, is_leading, dependsOn, dependedOn, redundant);

    // Clean up
    gf_isom_close(movie);

    return 0;
}