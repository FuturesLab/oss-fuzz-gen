#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

// Define a macro for the GF_EXPORT attribute if it's not already defined
#ifndef GF_EXPORT
#define GF_EXPORT
#endif

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure we have enough data for the trackNumber and StreamDescriptionIndex
    if (size < sizeof(uint32_t) * 2) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and StreamDescriptionIndex from the data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t StreamDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));

    // Create a sample
    GF_ISOSample sample;
    sample.data = (uint8_t *)(data + sizeof(uint32_t) * 2);
    sample.dataLength = size - sizeof(uint32_t) * 2;
    sample.DTS = 0;
    sample.CTS_Offset = 0;
    sample.IsRAP = 1; // Random Access Point

    // Call the function-under-test
    gf_isom_add_sample(movie, trackNumber, StreamDescriptionIndex, &sample);

    // Clean up
    gf_isom_close(movie);

    return 0;
}