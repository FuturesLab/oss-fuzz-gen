#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    if (size < sizeof(u32) * 2 + sizeof(GF_ISOMTrackFlagOp)) {
        return 0;
    }

    // Create a new movie using the library's function
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract trackNumber, flags, and op from the data
    u32 trackNumber = *((u32 *)data);
    u32 flags = *((u32 *)(data + sizeof(u32)));
    GF_ISOMTrackFlagOp op = *((GF_ISOMTrackFlagOp *)(data + sizeof(u32) * 2));

    // Call the function-under-test
    gf_isom_set_track_flags(movie, trackNumber, flags, op);

    // Close the movie to clean up
    gf_isom_close(movie);

    return 0;
}