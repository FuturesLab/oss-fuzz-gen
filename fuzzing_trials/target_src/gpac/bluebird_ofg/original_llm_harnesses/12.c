#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // Include the stdbool.h library for boolean types
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    
    if (movie == NULL) {
        return 0;
    }

    // Ensure trackNumber is within a reasonable range
    u32 trackNumber = (size > 0) ? data[0] % 10 + 1 : 1; // Assuming there are at least 10 tracks

    // Enable or disable the track based on the data
    bool enableTrack = (size > 1) ? (data[1] % 2 == 0) : true;  // Use 'bool' type and 'true' from stdbool.h

    // Call the function-under-test
    gf_isom_set_track_enabled(movie, trackNumber, enableTrack);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}