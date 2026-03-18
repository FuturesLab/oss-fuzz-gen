#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;

    // Initialize the movie object
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure trackNumber is within a reasonable range
    trackNumber = (u32)((size > 0) ? data[0] : 1);

    // Call the function under test
    gf_isom_remove_track(movie, trackNumber);

    // Close the movie object
    gf_isom_close(movie);

    return 0;
}