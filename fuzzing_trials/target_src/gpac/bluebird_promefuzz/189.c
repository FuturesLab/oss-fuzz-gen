#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_189(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + sizeof(Bool) + sizeof(u32)) return 0;

    GF_TextSample *sample = gf_isom_new_text_sample();
    if (!sample) return 0;

    u32 color = *(const u32 *)Data;
    Bool is_forced = *(const Bool *)(Data + sizeof(u32));
    u32 scroll_delay = *(const u32 *)(Data + sizeof(u32) + sizeof(Bool));

    // Fuzz gf_isom_text_reset_styles
    gf_isom_text_reset_styles(sample);

    // Fuzz gf_isom_text_set_highlight_color
    gf_isom_text_set_highlight_color(sample, color);

    // Fuzz gf_isom_text_set_forced
    gf_isom_text_set_forced(sample, is_forced);

    // Fuzz gf_isom_text_reset
    gf_isom_text_reset(sample);

    // Fuzz gf_isom_text_add_style
    GF_StyleRecord *style_record = (GF_StyleRecord *)malloc(sizeof(GF_StyleRecord));
    if (style_record) {
        gf_isom_text_add_style(sample, style_record);
        free(style_record);
    }

    // Fuzz gf_isom_text_set_scroll_delay
    gf_isom_text_set_scroll_delay(sample, scroll_delay);

    gf_isom_delete_text_sample(sample);

    return 0;
}