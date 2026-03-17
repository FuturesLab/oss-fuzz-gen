#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming a default track number
    u32 StreamDescriptionIndex = 1; // Assuming a default stream description index

    // Create a sample
    GF_ISOSample *sample = gf_isom_sample_new();
    if (!sample) {
        gf_isom_close(movie);
        return 0;
    }

    // Initialize sample data
    sample->dataLength = size;
    sample->data = (unsigned char *)malloc(size);
    if (sample->data) {
        memcpy(sample->data, data, size);
    }

    // Call the function-under-test
    gf_isom_add_sample(movie, trackNumber, StreamDescriptionIndex, sample);

    // Clean up
    gf_isom_sample_del(&sample);
    gf_isom_close(movie);

    return 0;
}