#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_253(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("test.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!the_file) return 0;

    u32 trackNumber = 1; // Assuming a valid track number
    u32 HintDescriptionIndex = 1; // Assuming a valid hint description index
    u32 TimeScale = 90000; // A common timescale for RTP

    // Call the function-under-test
    gf_isom_rtp_set_timescale(the_file, trackNumber, HintDescriptionIndex, TimeScale);

    gf_isom_close(the_file);

    return 0;
}

#ifdef __cplusplus
}
#endif