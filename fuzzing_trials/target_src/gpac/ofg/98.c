#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for trackNumber and data
    if (size < sizeof(uint32_t) + 1) {
        return 0;
    }

    // Initialize a GF_ISOFile object
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_WRITE_EDIT, NULL);

    // Extract trackNumber from the data
    uint32_t trackNumber = *((uint32_t *)data);
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Use the remaining data as the sample data
    uint8_t *sampleData = (uint8_t *)data;
    uint32_t dataSize = (uint32_t)size;

    // Call the function-under-test
    gf_isom_append_sample_data(movie, trackNumber, sampleData, dataSize);

    // Clean up
    if (movie != NULL) {
        gf_isom_close(movie);
    }

    return 0;
}