#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract parameters
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize parameters for gf_isom_reset_track_switch_parameter
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber from the input data
    uint32_t trackNumber = *((uint32_t *)data);

    // Extract reset_all_group from the input data
    Bool reset_all_group = (Bool)(data[sizeof(uint32_t)] % 2);

    // Call the function-under-test
    gf_isom_reset_track_switch_parameter(movie, trackNumber, reset_all_group);

    // Clean up
    gf_isom_close(movie);

    return 0;
}