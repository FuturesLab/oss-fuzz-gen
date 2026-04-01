#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_284(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the trackNumber is a valid non-zero value
    u32 trackNumber = size > 0 ? (u32)data[0] : 1;

    // Call the function-under-test
    gf_isom_remove_track_from_root_od(movie, trackNumber);

    // Clean up
    gf_isom_close(movie);

    return 0;
}