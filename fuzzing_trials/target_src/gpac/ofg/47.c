#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a u32 value
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Allocate and initialize a GF_ISOFile structure
    // Provide a third argument for the temporary directory, using NULL
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Extract a u32 value from the input data
    uint32_t OD_ID = *((uint32_t *)data);

    // Call the function-under-test
    gf_isom_set_root_od_id(movie, OD_ID);

    // Clean up
    gf_isom_close(movie);

    return 0;
}