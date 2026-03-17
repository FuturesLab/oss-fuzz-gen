#include <stdint.h>
#include <stdlib.h>
#include <gpac/constants.h>
#include <gpac/isomedia.h>  // Include the necessary header for GF_ISOFile and related functions
#include <gpac/tools.h>     // Include the necessary header for Bool and other related types

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    GF_ISOTrackID TrackID = 1;  // Assuming a valid track ID
    u32 flags = 0;  // Example flags value
    u32 subSampleSize = size > 0 ? data[0] : 1;  // Example subsample size
    u8 priority = size > 1 ? data[1] : 0;  // Example priority
    u32 reserved = 0;  // Example reserved value
    Bool discardable = size > 2 ? (Bool)(data[2] % 2) : GF_FALSE;  // Example discardable value

    // Call the function-under-test
    gf_isom_fragment_add_subsample(movie, TrackID, flags, subSampleSize, priority, reserved, discardable);

    // Clean up
    gf_isom_close(movie);

    return 0;
}