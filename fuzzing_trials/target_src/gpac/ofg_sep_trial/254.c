#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure non-zero values for trackNumber, HintDescriptionIndex, and TimeScale
    u32 trackNumber = size > 0 ? data[0] : 1;
    u32 HintDescriptionIndex = size > 1 ? data[1] : 1;
    u32 TimeScale = size > 2 ? data[2] : 1;

    // Call the function-under-test
    gf_isom_rtp_set_timescale(the_file, trackNumber, HintDescriptionIndex, TimeScale);

    // Close the file
    gf_isom_close(the_file);

    return 0;
}