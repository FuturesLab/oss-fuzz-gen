#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming track number 1 for testing

    GF_ISOSample *sample = gf_isom_sample_new();
    if (!sample) {
        gf_isom_close(movie);
        return 0;
    }

    // Set sample data
    sample->dataLength = size;
    sample->data = (unsigned char *)malloc(size);
    if (!sample->data) {
        gf_isom_sample_del(&sample);
        gf_isom_close(movie);
        return 0;
    }
    memcpy(sample->data, data, size);

    // Call the function-under-test
    gf_isom_add_sample_shadow(movie, trackNumber, sample);

    // Clean up
    gf_isom_sample_del(&sample);
    gf_isom_close(movie);

    return 0;
}