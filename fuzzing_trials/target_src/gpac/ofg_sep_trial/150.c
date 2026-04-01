#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the data size is sufficient
    if (size < sizeof(uint32_t) + 1) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber from the data
    uint32_t trackNumber = *((uint32_t *)data);
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Call the function-under-test
    gf_isom_add_user_data_boxes(movie, trackNumber, (uint8_t *)data, (uint32_t)size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}