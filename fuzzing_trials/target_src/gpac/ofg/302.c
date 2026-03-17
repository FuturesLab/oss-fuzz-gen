#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Include the header that defines GF_TextSample

int LLVMFuzzerTestOneInput_302(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for extracting a 32-bit ARGB value
    if (size < sizeof(uint32_t) || data == NULL) {
        return 0;
    }

    // Initialize a GF_TextSample object
    GF_TextSample textSample;
    // Initialize the fields of textSample to avoid undefined behavior
    textSample.text = NULL;
    textSample.len = 0;
    textSample.styles = NULL;
    textSample.highlight_color = NULL;
    textSample.scroll_delay = NULL;
    textSample.box = NULL;
    textSample.wrap = NULL;
    textSample.is_forced = 0;
    textSample.others = NULL;
    textSample.cur_karaoke = NULL;

    // Extract a 32-bit ARGB value from the input data
    uint32_t argb = *((uint32_t *)data);

    // Call the function-under-test
    gf_isom_text_set_highlight_color(&textSample, argb);

    return 0;
}