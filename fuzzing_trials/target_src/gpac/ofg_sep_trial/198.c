#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    GF_ISOSample *sample = gf_isom_sample_new();
    u64 dataOffset = 0;

    // Ensure movie and sample are not NULL
    if (movie == NULL || sample == NULL) {
        if (movie != NULL) {
            gf_isom_close(movie);
        }
        if (sample != NULL) {
            gf_isom_sample_del(&sample);
        }
        return 0;
    }

    // Fuzz the function
    gf_isom_add_sample_reference(movie, trackNumber, StreamDescriptionIndex, sample, dataOffset);

    // Clean up
    gf_isom_close(movie);
    gf_isom_sample_del(&sample);

    return 0;
}