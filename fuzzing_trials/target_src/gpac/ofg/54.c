#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure we have enough data for trakID, refTrakID, MediaType, and TimeScale
    if (size < sizeof(GF_ISOTrackID) * 2 + sizeof(u32) * 2 + 1) {
        return 0;
    }

    // Initialize variables for the function call
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    GF_ISOTrackID trakID = *(GF_ISOTrackID *)data;
    GF_ISOTrackID refTrakID = *(GF_ISOTrackID *)(data + sizeof(GF_ISOTrackID));
    u32 MediaType = *(u32 *)(data + sizeof(GF_ISOTrackID) * 2);
    u32 TimeScale = *(u32 *)(data + sizeof(GF_ISOTrackID) * 2 + sizeof(u32));

    // Ensure the URI is null-terminated
    size_t uri_offset = sizeof(GF_ISOTrackID) * 2 + sizeof(u32) * 2;
    size_t uri_length = size - uri_offset;
    char uri[256]; // Assume a max URI length of 255 for this example
    if (uri_length > 255) {
        uri_length = 255;
    }
    memcpy(uri, data + uri_offset, uri_length);
    uri[uri_length] = '\0';

    // Call the function-under-test
    gf_isom_new_external_track(movie, trakID, refTrakID, MediaType, TimeScale, uri);

    // Clean up
    gf_isom_close(movie);

    return 0;
}