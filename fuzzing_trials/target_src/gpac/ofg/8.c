#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>  // Include the header that defines GF_ISOM_OPEN_READWRITE
#include <gpac/internal/isomedia_dev.h>  // Additional header that might define GF_ISOM_OPEN_READWRITE

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);  // Use GF_ISOM_OPEN_WRITE if GF_ISOM_OPEN_READWRITE is not available
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient for extracting values
    if (size < sizeof(GF_ISOTrackID) + 2 * sizeof(u64)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract parameters from data
    GF_ISOTrackID reference_track_ID = *(GF_ISOTrackID *)data;
    u64 ntp_in_track_timescale = *(u64 *)(data + sizeof(GF_ISOTrackID));
    u64 traf_duration_in_track_timescale = *(u64 *)(data + sizeof(GF_ISOTrackID) + sizeof(u64));

    // Call the function-under-test
    gf_isom_set_traf_mss_timeext(movie, reference_track_ID, ntp_in_track_timescale, traf_duration_in_track_timescale);

    // Clean up
    gf_isom_close(movie);

    return 0;
}