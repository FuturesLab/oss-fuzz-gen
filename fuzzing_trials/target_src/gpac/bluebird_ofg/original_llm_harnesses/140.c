#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract parameters
    if (size < sizeof(uint32_t) * 3) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t dur_num = *((uint32_t *)(data + sizeof(uint32_t)));
    uint32_t dur_den = *((uint32_t *)(data + 2 * sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_set_last_sample_duration_ex(movie, trackNumber, dur_num, dur_den);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}