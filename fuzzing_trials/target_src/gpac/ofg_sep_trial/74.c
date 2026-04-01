#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/internal/isomedia_dev.h>  // Include the internal header where GF_TextSample is fully defined

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract start_char and end_char
    if (size < 4) {
        return 0;
    }

    // Initialize the GF_TextSample structure
    GF_TextSample samp;
    samp.text = NULL;
    samp.len = 0;
    samp.styles = NULL;
    samp.highlight_color = NULL;
    samp.scroll_delay = NULL;
    samp.box = NULL;
    samp.wrap = NULL;
    samp.is_forced = 0;
    samp.others = NULL;
    samp.cur_karaoke = NULL;

    // Extract start_char and end_char from the data
    uint16_t start_char = (uint16_t)((data[0] << 8) | data[1]);
    uint16_t end_char = (uint16_t)((data[2] << 8) | data[3]);

    // Call the function-under-test
    gf_isom_text_add_highlight(&samp, start_char, end_char);

    return 0;
}