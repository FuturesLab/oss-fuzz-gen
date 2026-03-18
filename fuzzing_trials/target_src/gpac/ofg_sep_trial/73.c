#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h>  // Include the internal header for complete type definitions

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_TextSample *samp = NULL;
    u16 start_char = 0;
    u16 end_char = 0;

    // Ensure the data size is sufficient to extract start_char and end_char
    if (size < 4) {
        return 0;
    }

    // Allocate memory for GF_TextSample
    samp = (GF_TextSample *)malloc(sizeof(GF_TextSample));
    if (!samp) {
        return 0;
    }

    // Initialize the GF_TextSample structure
    memset(samp, 0, sizeof(GF_TextSample));  // Ensure all fields are initialized to zero
    samp->text = (char *)malloc(size + 1);  // Allocate extra byte for null-termination
    if (!samp->text) {
        free(samp);
        return 0;
    }
    // Copy data into the text field of GF_TextSample
    memcpy(samp->text, data, size);
    samp->text[size] = '\0';  // Null-terminate the text
    samp->len = size;  // Use the correct member name 'len'

    // Extract start_char and end_char from the input data
    start_char = (u16)((data[0] << 8) | data[1]);
    end_char = (u16)((data[2] << 8) | data[3]);

    // Ensure start_char and end_char are within valid bounds
    if (start_char > end_char || end_char >= size) {
        // Clean up
        free(samp->text);
        free(samp);
        return 0;
    }

    // Call the function-under-test
    gf_isom_text_add_highlight(samp, start_char, end_char);

    // Clean up
    free(samp->text);
    free(samp);

    return 0;
}