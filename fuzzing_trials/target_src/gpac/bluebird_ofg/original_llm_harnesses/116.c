#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract necessary parameters
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize the GF_ISOFile structure with a temporary directory
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp");

    // Check if movie is initialized properly
    if (!movie) {
        return 0;
    }

    // Extract trackNumber and StreamDescriptionIndex from the data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t StreamDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));

    // Create a new GF_ESD structure manually (as the gf_isom_new_esd does not exist)
    GF_ESD newESD;
    memset(&newESD, 0, sizeof(GF_ESD));

    // Call the function under test
    gf_isom_change_mpeg4_description(movie, trackNumber, StreamDescriptionIndex, &newESD);

    // Clean up
    gf_isom_close(movie);

    return 0;
}