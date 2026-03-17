#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for extracting necessary values
    if (size < sizeof(uint32_t) * 3) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract values from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t HintDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));
    uint32_t TimeOffset = *((uint32_t *)(data + 2 * sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_rtp_set_time_offset(the_file, trackNumber, HintDescriptionIndex, TimeOffset);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}