#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract necessary parameters
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize the parameters for gf_isom_remove_sample_group
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract track and grouping_type from the input data
    uint32_t track = *((uint32_t *)data);
    uint32_t grouping_type = *((uint32_t *)(data + sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_remove_sample_group(movie, track, grouping_type);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}