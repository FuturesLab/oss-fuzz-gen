#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    GF_ISOTrackID TrackID = 1; // Assuming a valid track ID
    u64 decode_time = 0;

    // Ensure movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Use the first 8 bytes of data as the decode_time if available
    if (size >= 8) {
        decode_time = *((u64 *)data);
    }

    // Call the function with the initialized parameters
    gf_isom_set_traf_base_media_decode_time(movie, TrackID, decode_time);

    // Clean up
    gf_isom_close(movie);

    return 0;
}