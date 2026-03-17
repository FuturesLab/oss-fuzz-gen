#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h> // Include for Bool type
#include <gpac/isomedia.h> // Include for GF_ISOFile and related functions

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting parameters
    if (size < sizeof(uint32_t) + 1) {
        return 0;
    }

    // Initialize parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract trackNumber from data
    uint32_t trackNumber = *((uint32_t *)data);

    // Extract CompactionOn from data
    Bool CompactionOn = (Bool)(data[sizeof(uint32_t)] % 2);

    // Call the function-under-test
    gf_isom_use_compact_size(movie, trackNumber, CompactionOn);

    // Clean up
    gf_isom_close(movie);

    return 0;
}