#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u32 dur_num;
    u32 dur_den;

    // Ensure size is sufficient for extracting required parameters
    if (size < sizeof(u32) * 3) {
        return 0;
    }

    // Initialize movie with a non-null input to maximize fuzzing results
    movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the input data
    trackNumber = *(const u32 *)(data);
    dur_num = *(const u32 *)(data + sizeof(u32));
    dur_den = *(const u32 *)(data + 2 * sizeof(u32));

    // Call the function under test
    gf_isom_set_last_sample_duration_ex(movie, trackNumber, dur_num, dur_den);

    // Close the movie
    gf_isom_close(movie);

    return 0;
}