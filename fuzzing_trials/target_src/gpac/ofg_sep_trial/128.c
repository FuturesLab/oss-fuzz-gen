#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber;

    // Initialize the movie with a non-NULL value
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Exit if the movie could not be opened
    }

    // Ensure trackNumber is within a valid range
    if (size < sizeof(u32)) {
        gf_isom_close(movie);
        return 0; // Exit if not enough data to set trackNumber
    }
    trackNumber = *((u32 *)data);

    // Call the function-under-test
    gf_isom_remove_edits(movie, trackNumber);

    // Clean up
    gf_isom_close(movie);

    return 0;
}