#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure the input size is adequate for the parameters
    if (size < sizeof(GF_ISOTrackID) + sizeof(u8) + sizeof(u32)) {
        return 0;
    }

    // Initialize the parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the input data
    GF_ISOTrackID TrackID = *(GF_ISOTrackID *)data;
    data += sizeof(GF_ISOTrackID);
    size -= sizeof(GF_ISOTrackID);

    u8 force_traf_flags = *data;
    data += sizeof(u8);
    size -= sizeof(u8);

    u32 boxes_size = (u32)size;
    u8 *boxes = (u8 *)malloc(boxes_size);
    if (!boxes) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy the remaining data into the boxes array
    memcpy(boxes, data, boxes_size);

    // Call the function-under-test
    gf_isom_setup_track_fragment_template(movie, TrackID, boxes, boxes_size, force_traf_flags);

    // Clean up
    free(boxes);
    gf_isom_close(movie);

    return 0;
}