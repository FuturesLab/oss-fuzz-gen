#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber;
    u32 duration;

    // Ensure size is sufficient to extract trackNumber and duration
    if (size < 8) {
        return 0;
    }

    // Initialize trackNumber and duration from the input data
    trackNumber = *(u32 *)data;
    duration = *(u32 *)(data + 4);

    // Create a new ISOFile for testing
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_last_sample_duration(movie, trackNumber, duration);

    // Clean up and close the movie
    gf_isom_close(movie);

    return 0;
}