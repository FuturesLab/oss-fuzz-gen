#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Include this for internal structures

int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to extract a start_time
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize a GF_TextSample
    GF_TextSample samp;
    samp.len = size; // Corrected from samp.sample_size to samp.len
    samp.text = (char*)malloc(size);
    if (samp.text == NULL) {
        return 0;
    }

    // Copy data into the text sample
    memcpy(samp.text, data, size);

    // Extract start_time from the data
    uint32_t start_time = *((uint32_t*)data);

    // Call the function-under-test
    gf_isom_text_add_karaoke(&samp, start_time);

    // Clean up
    free(samp.text);

    return 0;
}