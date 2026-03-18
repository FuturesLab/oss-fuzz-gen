#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/tools.h> // Include for u32 and u64 type definitions

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Create a new empty ISO file in memory
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Assuming the first track for simplicity
    u32 trackNumber = 1;
    u64 dur = 1000; // Arbitrary non-zero duration

    // Attempt to force the track duration
    gf_isom_force_track_duration(movie, trackNumber, dur);

    // Close the ISO file
    gf_isom_close(movie);

    return 0;
}