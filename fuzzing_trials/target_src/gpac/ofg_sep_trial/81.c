#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Include the internal header for full struct definition

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to extract start_char and end_char
    }

    // Initialize the GF_TextSample structure
    GF_TextSample samp;
    samp.text = (char *)data; // Assuming the text is part of the input data
    samp.len = size;          // The length of the text

    // Extract start_char and end_char from the input data
    u16 start_char = (u16)data[0] | ((u16)data[1] << 8);
    u16 end_char = (u16)data[2] | ((u16)data[3] << 8);

    // Call the function under test
    gf_isom_text_add_blink(&samp, start_char, end_char);

    return 0;
}