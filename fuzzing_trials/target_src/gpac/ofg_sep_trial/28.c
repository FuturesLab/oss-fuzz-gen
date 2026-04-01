#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure size is large enough to extract uint32_t values
    if (size < sizeof(uint32_t) * 3) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract uint32_t values from data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t HintDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));
    uint32_t SequenceNumberOffset = *((uint32_t *)(data + 2 * sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_rtp_set_time_sequence_offset(the_file, trackNumber, HintDescriptionIndex, SequenceNumberOffset);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}