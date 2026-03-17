#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *movie;
    GF_ISOTrackID trakID;
    GF_ISOTrackID refTrakID;
    u32 MediaType;
    u32 TimeScale;
    char uri[256];

    // Ensure the data size is sufficient to extract required values
    if (size < sizeof(GF_ISOTrackID) * 2 + sizeof(u32) * 2 + 1) {
        return 0;
    }

    // Assign values to the parameters from the input data
    trakID = *(GF_ISOTrackID *)data;
    refTrakID = *(GF_ISOTrackID *)(data + sizeof(GF_ISOTrackID));
    MediaType = *(u32 *)(data + sizeof(GF_ISOTrackID) * 2);
    TimeScale = *(u32 *)(data + sizeof(GF_ISOTrackID) * 2 + sizeof(u32));
    size_t uri_size = size - (sizeof(GF_ISOTrackID) * 2 + sizeof(u32) * 2);
    if (uri_size >= sizeof(uri)) {
        uri_size = sizeof(uri) - 1;
    }
    memcpy(uri, data + sizeof(GF_ISOTrackID) * 2 + sizeof(u32) * 2, uri_size);
    uri[uri_size] = '\0'; // Ensure null-terminated string

    // Create a dummy GF_ISOFile object
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);

    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_new_external_track(movie, trakID, refTrakID, MediaType, TimeScale, uri);

    // Clean up
    gf_isom_close(movie);

    return 0;
}