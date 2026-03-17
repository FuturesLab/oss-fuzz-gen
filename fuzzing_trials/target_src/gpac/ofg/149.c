#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the required parameters
    if (size < sizeof(uint32_t) + 1) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract a track number from the data
    uint32_t trackNumber = *((uint32_t*)data);
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Use the remaining data as the user data
    uint8_t *userData = (uint8_t*)data;
    uint32_t dataLength = (uint32_t)size;

    // Call the function-under-test
    gf_isom_add_user_data_boxes(movie, trackNumber, userData, dataLength);

    // Clean up
    gf_isom_close(movie);

    return 0;
}