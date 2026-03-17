#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    GF_ISOSample sample;
    u32 trackNumber = 1; // Example track number
    u32 StreamDescriptionIndex = 1; // Example stream description index

    // Initialize the movie structure
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Initialize the sample structure
    sample.data = (u8 *)data; // Correct type for data
    sample.dataLength = size;
    sample.DTS = 0;
    sample.CTS_Offset = 0;
    sample.IsRAP = 1;
    // Removed non-existent fields: DependsOn, HasRedundancy, PaddingBits, DegradationPriority

    // Call the function-under-test
    gf_isom_add_sample(movie, trackNumber, StreamDescriptionIndex, &sample);

    // Close the movie to clean up
    gf_isom_close(movie);

    return 0;
}