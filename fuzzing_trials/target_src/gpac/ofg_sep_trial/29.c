#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

// Define u32 if not defined in the included headers
typedef uint32_t u32;

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure the size is sufficient for extracting u32 values
    if (size < 12) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract u32 values from the input data
    u32 trackNumber = *((u32 *)data);
    u32 HintDescriptionIndex = *((u32 *)(data + 4));
    u32 SequenceNumberOffset = *((u32 *)(data + 8));

    // Call the function-under-test
    gf_isom_rtp_set_time_sequence_offset(the_file, trackNumber, HintDescriptionIndex, SequenceNumberOffset);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}