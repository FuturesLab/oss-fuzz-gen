#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract necessary parameters
    if (size < sizeof(uint32_t) * 4) {
        return 0;
    }

    // Initialize parameters for gf_isom_set_visual_info
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t StreamDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));
    uint32_t Width = *((uint32_t *)(data + 2 * sizeof(uint32_t)));
    uint32_t Height = *((uint32_t *)(data + 3 * sizeof(uint32_t)));

    // Call the function under test
    gf_isom_set_visual_info(movie, trackNumber, StreamDescriptionIndex, Width, Height);

    // Clean up
    gf_isom_close(movie);

    return 0;
}