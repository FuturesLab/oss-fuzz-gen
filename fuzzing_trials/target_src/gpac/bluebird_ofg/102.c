#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy and memset
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;  // Assuming track number 1 for testing
    u32 StreamDescriptionIndex = 1;  // Assuming stream description index 1 for testing
    GF_DOVIDecoderConfigurationRecord dvcc;

    // Ensure the dvcc structure is initialized and non-NULL
    if (size >= sizeof(GF_DOVIDecoderConfigurationRecord)) {
        memcpy(&dvcc, data, sizeof(GF_DOVIDecoderConfigurationRecord));
    } else {
        memset(&dvcc, 0, sizeof(GF_DOVIDecoderConfigurationRecord));
    }

    // Call the function-under-test
    gf_isom_set_dolby_vision_profile(movie, trackNumber, StreamDescriptionIndex, &dvcc);

    // Clean up
    if (movie) {
        gf_isom_close(movie);
    }

    return 0;
}