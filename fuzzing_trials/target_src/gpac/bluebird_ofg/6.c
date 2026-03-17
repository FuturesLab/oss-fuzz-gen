#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure there is at least one track in the movie
    // Provide the additional arguments: track ID and time scale
    gf_isom_new_track(movie, 1, GF_ISOM_MEDIA_VISUAL, 1000);

    // Use the first 4 bytes of data as the track number if available
    u32 trackNumber = 1; // Default track number
    if (size >= 4) {
        trackNumber = *((u32 *)data);
    }

    // Use the next 8 bytes of data as the creation time if available
    u64 ctime = 0; // Default creation time
    if (size >= 12) {
        ctime = *((u64 *)(data + 4));
    }

    // Use the next 8 bytes of data as the modification time if available
    u64 mtime = 0; // Default modification time
    if (size >= 20) {
        mtime = *((u64 *)(data + 12));
    }

    // Call the function-under-test
    gf_isom_set_track_creation_time(movie, trackNumber, ctime, mtime);

    // Clean up
    gf_isom_close(movie);

    return 0;
}