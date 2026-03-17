#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Initialize the parameters for the function gf_isom_add_subsample
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    u32 track = (size > 0) ? data[0] : 1; // Ensure track is non-zero
    u32 sampleNumber = (size > 1) ? data[1] : 1; // Ensure sampleNumber is non-zero
    u32 flags = (size > 2) ? data[2] : 0;
    u32 subSampleSize = (size > 3) ? data[3] : 1; // Ensure subSampleSize is non-zero
    u8 priority = (size > 4) ? data[4] : 0;
    u32 reserved = (size > 5) ? data[5] : 0;
    Bool discardable = (size > 6) ? (Bool)(data[6] % 2) : 0;

    // Call the function under test
    GF_Err result = gf_isom_add_subsample(movie, track, sampleNumber, flags, subSampleSize, priority, reserved, discardable);

    // Clean up the movie file
    gf_isom_close(movie);

    return 0;
}