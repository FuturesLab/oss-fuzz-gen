#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber = 1; // Example track number
    u32 sampleNumber = 1; // Example sample number
    Bool data_only = GF_FALSE; // Example boolean value

    // Ensure the size is sufficient for a GF_ISOSample structure
    if (size < sizeof(GF_ISOSample)) {
        return 0;
    }

    // Allocate memory for the sample
    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (!sample) {
        return 0;
    }

    // Initialize the sample with data from the fuzzer
    sample->dataLength = size;
    sample->data = (char *)data; // Directly use the fuzzer data as sample data

    // Create a dummy movie object
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        free(sample);
        return 0;
    }

    // Call the function under test
    gf_isom_update_sample(movie, trackNumber, sampleNumber, sample, data_only);

    // Clean up
    gf_isom_close(movie);
    free(sample);

    return 0;
}