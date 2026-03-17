#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u64 for_time;

    // Initialize the variables with non-NULL values
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL); // Open a dummy ISO file
    trackNumber = 1; // Use a valid track number
    for_time = 0; // Initialize for_time with a valid timestamp

    if (movie != NULL) {
        // Call the function-under-test
        gf_isom_get_sample_description_index(movie, trackNumber, for_time);

        // Close the movie file after use
        gf_isom_close(movie);
    }

    return 0;
}