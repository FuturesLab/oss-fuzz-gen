#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(GF_ISOSample) + 2 * sizeof(uint32_t) + 2 * sizeof(uint64_t)) {
        return 0;
    }

    // Initialize the parameters for gf_isom_update_sample_reference
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Use the data to set trackNumber and sampleNumber
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t sampleNumber = *((uint32_t *)(data + sizeof(uint32_t)));

    // Allocate and initialize a sample
    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (sample == NULL) {
        gf_isom_close(movie);
        return 0;
    }

    // Set some values in the sample using the data
    sample->DTS = *((uint64_t *)(data + 2 * sizeof(uint32_t)));
    sample->CTS_Offset = *((uint32_t *)(data + 2 * sizeof(uint32_t) + sizeof(uint64_t)));
    sample->IsRAP = 1; // Set IsRAP to a non-zero value

    // Set data_offset using the remaining data
    uint64_t data_offset = *((uint64_t *)(data + 2 * sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t)));

    // Call the function under test
    gf_isom_update_sample_reference(movie, trackNumber, sampleNumber, sample, data_offset);

    // Clean up
    gf_isom_close(movie);
    free(sample);

    return 0;
}