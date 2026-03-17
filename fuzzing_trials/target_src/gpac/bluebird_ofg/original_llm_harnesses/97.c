#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize with a valid track number

    // Create a new ISO file
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE | GF_ISOM_OPEN_READ, NULL);

    if (movie != NULL && size > 0) {
        // Directly call the function-under-test with the given track number
        gf_isom_remove_track_from_root_od(movie, trackNumber);

        // Close and release the ISO file
        gf_isom_close(movie);
    }

    return 0;
}