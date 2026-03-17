#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Include for GF_ISOTrackID and u32

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL); // Create a new ISO file
    if (movie == NULL) {
        return 0; // Return if movie creation failed
    }

    // Ensure there is enough data to extract trakID, MediaType, and TimeScale
    if (size < sizeof(GF_ISOTrackID) + sizeof(u32) * 2) {
        gf_isom_close(movie); // Clean up
        return 0;
    }

    // Extract trakID, MediaType, and TimeScale from the input data
    GF_ISOTrackID trakID = *(GF_ISOTrackID *)data;
    u32 MediaType = *(u32 *)(data + sizeof(GF_ISOTrackID));
    u32 TimeScale = *(u32 *)(data + sizeof(GF_ISOTrackID) + sizeof(u32));

    // Call the function-under-test
    gf_isom_new_track(movie, trakID, MediaType, TimeScale);

    // Clean up
    gf_isom_close(movie);

    return 0;
}