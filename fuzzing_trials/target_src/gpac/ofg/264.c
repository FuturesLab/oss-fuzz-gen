#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Initialize trackNumber, sampleNumber, and data_offset
    u32 trackNumber = 1;
    u32 sampleNumber = 1;
    u64 data_offset = 0;

    // Initialize the GF_ISOSample structure
    GF_ISOSample *sample = gf_isom_sample_new();
    if (!sample) {
        gf_isom_close(movie);
        return 0;
    }

    // Populate the sample with some data from the input
    if (size > 0) {
        sample->dataLength = size;
        sample->data = (char *)malloc(size);
        if (sample->data) {
            memcpy(sample->data, data, size);
        }
    }

    // Call the function-under-test
    gf_isom_update_sample_reference(movie, trackNumber, sampleNumber, sample, data_offset);

    // Clean up
    gf_isom_sample_del(&sample);
    gf_isom_close(movie);

    return 0;
}