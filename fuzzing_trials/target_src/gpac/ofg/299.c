#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_299(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    GF_ISOTrackID trakID;
    u32 MediaType;
    u32 TimeScale;

    // Ensure size is sufficient to extract necessary parameters
    if (size < sizeof(GF_ISOTrackID) + 2 * sizeof(u32)) {
        return 0;
    }

    // Initialize parameters from the input data
    trakID = *(GF_ISOTrackID *)data;
    MediaType = *(u32 *)(data + sizeof(GF_ISOTrackID));
    TimeScale = *(u32 *)(data + sizeof(GF_ISOTrackID) + sizeof(u32));

    // Create a new ISO file (movie) for testing
    movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);

    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_new_track(movie, trakID, MediaType, TimeScale);

    // Close and clean up the movie
    gf_isom_close(movie);

    return 0;
}