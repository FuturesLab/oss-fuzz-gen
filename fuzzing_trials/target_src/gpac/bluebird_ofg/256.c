#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber;
    Bool enableTrack;

    if (size < sizeof(u32) + sizeof(Bool)) {
        return 0;
    }

    // Initialize trackNumber and enableTrack from the input data
    trackNumber = *((u32 *)data);
    enableTrack = *((Bool *)(data + sizeof(u32)));

    // Create a new ISO file for testing
    movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_track_enabled(movie, trackNumber, enableTrack);

    // Close and cleanup
    gf_isom_close(movie);

    return 0;
}