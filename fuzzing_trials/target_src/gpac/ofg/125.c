#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <gpac/isomedia.h> // Assuming this is the correct header for the function

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    GF_ISOTrackID trakID = 1; // Example track ID
    GF_ISOTrackID refTrakID = 2; // Example reference track ID
    u32 MediaType = GF_ISOM_MEDIA_VISUAL; // Example media type
    u32 TimeScale = 1000; // Example time scale
    char uri[256]; // Buffer for URI

    // Ensure data is large enough to populate URI
    if (size < sizeof(uri)) {
        return 0;
    }

    // Copy data into URI, ensuring null-termination
    memcpy(uri, data, sizeof(uri) - 1);
    uri[sizeof(uri) - 1] = '\0';

    // Call the function-under-test
    gf_isom_new_external_track(movie, trakID, refTrakID, MediaType, TimeScale, uri);

    // Clean up
    gf_isom_close(movie);

    return 0;
}