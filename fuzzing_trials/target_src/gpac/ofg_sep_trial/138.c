#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    GF_ISOTrackID TrackID = 1; // Assuming a valid TrackID for fuzzing
    u64 decode_time = 0;

    // Ensure size is sufficient for extracting a u64 value
    if (size >= sizeof(u64)) {
        decode_time = *(const u64*)data;
    }

    // Call the function-under-test
    gf_isom_set_traf_base_media_decode_time(movie, TrackID, decode_time);

    // Clean up
    gf_isom_close(movie);

    return 0;
}