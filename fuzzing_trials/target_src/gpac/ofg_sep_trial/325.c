#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Added this line to include the full definition of GF_TextSample

int LLVMFuzzerTestOneInput_325(const uint8_t *data, size_t size) {
    if (size < sizeof(int16_t) * 4) {
        // Ensure there's enough data for four int16_t values
        return 0;
    }

    // Initialize the sample
    GF_TextSample sample;
    sample.text = (char *)data; // Assigning data as text for the sample
    sample.len = size; // Assigning size as the length of the text

    // Extract int16_t values from the data
    int16_t top = *((int16_t *)data);
    int16_t left = *((int16_t *)(data + sizeof(int16_t)));
    int16_t bottom = *((int16_t *)(data + 2 * sizeof(int16_t)));
    int16_t right = *((int16_t *)(data + 3 * sizeof(int16_t)));

    // Call the function-under-test
    gf_isom_text_set_box(&sample, top, left, bottom, right);

    return 0;
}