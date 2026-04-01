#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    GF_ISOTrackID TrackID = 1; // Assuming track ID starts from 1
    u32 flags = 0;
    u32 subSampleSize = size > 0 ? data[0] : 1; // Avoid zero size
    u8 priority = size > 1 ? data[1] : 1; // Avoid zero priority
    u32 reserved = 0;
    Bool discardable = GF_FALSE;

    if (!movie) {
        return 0; // Exit if movie creation failed
    }

    // Call the function-under-test
    GF_Err result = gf_isom_fragment_add_subsample(movie, TrackID, flags, subSampleSize, priority, reserved, discardable);

    // Clean up
    gf_isom_close(movie);

    return 0;
}