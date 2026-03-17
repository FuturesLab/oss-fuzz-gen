#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read from
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract trackNumber from the data
    uint32_t trackNumber = *((uint32_t *)data);

    // Set reset_all_group based on the data
    Bool reset_all_group = (Bool)(data[sizeof(uint32_t)] % 2);

    // Call the function-under-test
    gf_isom_reset_track_switch_parameter(movie, trackNumber, reset_all_group);

    // Clean up
    gf_isom_close(movie);

    return 0;
}