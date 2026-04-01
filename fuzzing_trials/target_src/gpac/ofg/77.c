#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize necessary structures
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the size is sufficient for the parameters
    if (size < sizeof(uint32_t) * 2 + sizeof(uint64_t)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract parameters from the data
    uint32_t trackNumber = *((uint32_t*)data);
    uint32_t StreamDescriptionIndex = *((uint32_t*)(data + sizeof(uint32_t)));
    uint64_t dataOffset = *((uint64_t*)(data + sizeof(uint32_t) * 2));

    // Create a sample
    GF_ISOSample *sample = gf_isom_sample_new();
    if (!sample) {
        gf_isom_close(movie);
        return 0;
    }

    // Fill the sample with some data
    sample->dataLength = size - (sizeof(uint32_t) * 2 + sizeof(uint64_t));
    sample->data = (char*)malloc(sample->dataLength);
    if (sample->data) {
        memcpy(sample->data, data + sizeof(uint32_t) * 2 + sizeof(uint64_t), sample->dataLength);
    }

    // Call the function under test
    gf_isom_add_sample_reference(movie, trackNumber, StreamDescriptionIndex, sample, dataOffset);

    // Clean up
    gf_isom_sample_del(&sample);
    gf_isom_close(movie);

    return 0;
}