// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_new_text_sample at tx3g.c:602:16 in isomedia.h
// gf_isom_text_reset_styles at tx3g.c:612:8 in isomedia.h
// gf_isom_text_set_highlight_color at tx3g.c:321:8 in isomedia.h
// gf_isom_text_set_forced at tx3g.c:423:8 in isomedia.h
// gf_isom_text_reset at tx3g.c:636:8 in isomedia.h
// gf_isom_text_add_style at tx3g.c:290:8 in isomedia.h
// gf_isom_text_set_scroll_delay at tx3g.c:358:8 in isomedia.h
// gf_isom_delete_text_sample at tx3g.c:646:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
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