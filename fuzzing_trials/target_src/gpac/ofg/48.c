#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 OD_ID;

    // Ensure size is sufficient to extract OD_ID
    if (size < sizeof(u32)) {
        return 0;
    }

    // Initialize movie object
    movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract OD_ID from the input data
    OD_ID = *((u32 *)data);

    // Call the function-under-test
    gf_isom_set_root_od_id(movie, OD_ID);

    // Clean up
    gf_isom_close(movie);

    return 0;
}