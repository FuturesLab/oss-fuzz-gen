#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memset
#include <gpac/isomedia.h> // Assuming this header contains the definition for GF_TextSample
#include <gpac/constants.h> // Include any additional headers that might define related constants or functions
#include <gpac/internal/isomedia_dev.h> // Include for the full definition of GF_TextSample

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Ensure we have enough data for start_char and end_char
    if (size < 4) {
        return 0;
    }

    // Initialize the parameters
    GF_TextSample samp;
    memset(&samp, 0, sizeof(GF_TextSample)); // Zero out the structure

    // Extract start_char and end_char from the input data
    u16 start_char = (u16)((data[0] << 8) | data[1]);
    u16 end_char = (u16)((data[2] << 8) | data[3]);

    // Call the function-under-test
    gf_isom_text_add_blink(&samp, start_char, end_char);

    return 0;
}