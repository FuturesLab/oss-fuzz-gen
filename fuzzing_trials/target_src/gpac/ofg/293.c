#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract the required parameters
    if (size < sizeof(uint32_t) * 4) {
        return 0;
    }

    // Initialize parameters
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t trackNumber = *((uint32_t *) data);
    uint32_t newTS = *((uint32_t *) (data + sizeof(uint32_t)));
    uint32_t new_tsinc = *((uint32_t *) (data + 2 * sizeof(uint32_t)));
    uint32_t force_rescale_type = *((uint32_t *) (data + 3 * sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_set_media_timescale(the_file, trackNumber, newTS, new_tsinc, force_rescale_type);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}