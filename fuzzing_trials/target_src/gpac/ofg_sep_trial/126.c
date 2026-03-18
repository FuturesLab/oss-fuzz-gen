#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h> // Include necessary header for GF_ISOFile and related functions

extern int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Initialize all necessary variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // If movie creation fails, return early
    }

    GF_ISOTrackID trakID = 1; // Example track ID, non-zero
    GF_ISOTrackID refTrakID = 2; // Example reference track ID, non-zero
    u32 MediaType = GF_ISOM_MEDIA_VISUAL; // Example media type
    u32 TimeScale = 1000; // Example time scale, non-zero
    char uri[256] = "http://example.com"; // Example URI, non-NULL

    // Call the function-under-test
    gf_isom_new_external_track(movie, trakID, refTrakID, MediaType, TimeScale, uri);

    // Clean up
    gf_isom_close(movie);

    return 0;
}