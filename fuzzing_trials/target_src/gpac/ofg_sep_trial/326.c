#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h> // Include the header file for GF_TextSample and gf_isom_text_set_box
#include <gpac/internal/isomedia_dev.h> // Include the internal header for the full definition of GF_TextSample

extern int LLVMFuzzerTestOneInput_326(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for gf_isom_text_set_box
    GF_TextSample samp;
    s16 top = 0;
    s16 left = 0;
    s16 bottom = 0;
    s16 right = 0;

    // Ensure we have enough data to extract values for top, left, bottom, and right
    if (size < 8) {
        return 0; // Not enough data
    }

    // Initialize the parameters using the input data
    top = (s16)data[0] | ((s16)data[1] << 8);
    left = (s16)data[2] | ((s16)data[3] << 8);
    bottom = (s16)data[4] | ((s16)data[5] << 8);
    right = (s16)data[6] | ((s16)data[7] << 8);

    // Call the function-under-test
    gf_isom_text_set_box(&samp, top, left, bottom, right);

    return 0;
}