#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure we have at least 4 bytes to form a u32
    if (size < 4) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract a u32 from the data
    uint32_t OD_ID = (uint32_t)data[0] | ((uint32_t)data[1] << 8) | ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 24);

    // Call the function under test
    gf_isom_set_root_od_id(movie, OD_ID);

    // Clean up
    gf_isom_close(movie);

    return 0;
}