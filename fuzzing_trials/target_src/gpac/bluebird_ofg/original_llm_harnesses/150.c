#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL); // Open a dummy file
    u32 trackNumber = 1; // Assuming track number 1 for testing
    u32 sampleNumber = 1; // Assuming sample number 1 for testing
    GF_ISOSample sample;
    u64 data_offset = 0; // Assuming data offset 0 for testing

    if (!movie) {
        return 0; // If movie is not opened, return early
    }

    // Initialize GF_ISOSample structure
    sample.data = (unsigned char *)data;
    sample.dataLength = size;
    sample.DTS = 0;
    sample.CTS_Offset = 0;
    sample.IsRAP = 1;

    // Call the function under test
    gf_isom_update_sample_reference(movie, trackNumber, sampleNumber, &sample, data_offset);

    // Clean up
    gf_isom_close(movie);

    return 0;
}