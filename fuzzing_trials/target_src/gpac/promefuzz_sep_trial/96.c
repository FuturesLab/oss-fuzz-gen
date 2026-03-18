// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_text_sample_size at tx3g.c:498:5 in isomedia.h
// gf_isom_text_set_highlight_color at tx3g.c:321:8 in isomedia.h
// gf_isom_text_add_karaoke at tx3g.c:335:8 in isomedia.h
// gf_isom_text_set_scroll_delay at tx3g.c:358:8 in isomedia.h
// gf_isom_text_add_text at tx3g.c:259:8 in isomedia.h
// gf_isom_text_set_karaoke_segment at tx3g.c:345:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Dummy definitions to satisfy the compiler
typedef struct {
    void *dummy;
} GF_TextStyleBox, GF_TextHighlightColorBox, GF_TextScrollDelayBox, GF_TextBoxBox, GF_TextWrapBox, GF_TextKaraokeBox;

// Dummy definition of GF_TextSample to satisfy the compiler
// Actual structure should be defined in isomedia.h, this is just for compilation
struct _3gpp_text_sample {
    char *text;
    u32 len;
    GF_TextStyleBox *styles;
    GF_TextHighlightColorBox *highlight_color;
    GF_TextScrollDelayBox *scroll_delay;
    GF_TextBoxBox *box;
    GF_TextWrapBox *wrap;
    Bool is_forced;
    GF_List *others;
    GF_TextKaraokeBox *cur_karaoke;
};

static GF_TextSample* create_sample() {
    GF_TextSample* sample = (GF_TextSample*)malloc(sizeof(GF_TextSample));
    if (sample) {
        memset(sample, 0, sizeof(GF_TextSample));
    }
    return sample;
}

static void free_sample(GF_TextSample* sample) {
    if (sample) {
        free(sample->text);
        free(sample);
    }
}

int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there is enough data for a u32

    GF_TextSample *sample = create_sample();
    if (!sample) return 0;

    // Fuzz gf_isom_text_sample_size
    u32 size = gf_isom_text_sample_size(sample);

    // Fuzz gf_isom_text_set_highlight_color
    if (Size >= sizeof(u32)) {
        u32 color = *((u32*)Data);
        gf_isom_text_set_highlight_color(sample, color);
    }

    // Fuzz gf_isom_text_add_karaoke
    if (Size >= sizeof(u32)) {
        u32 start_time = *((u32*)Data);
        gf_isom_text_add_karaoke(sample, start_time);
    }

    // Fuzz gf_isom_text_set_scroll_delay
    if (Size >= sizeof(u32)) {
        u32 scroll_delay = *((u32*)Data);
        gf_isom_text_set_scroll_delay(sample, scroll_delay);
    }

    // Fuzz gf_isom_text_add_text
    if (Size > sizeof(u32)) {
        char *text_data = (char*)(Data + sizeof(u32));
        u32 text_len = Size - sizeof(u32);
        gf_isom_text_add_text(sample, text_data, text_len);
    }

    // Fuzz gf_isom_text_set_karaoke_segment
    if (Size >= 2 * sizeof(u32) + 2 * sizeof(u16)) {
        u32 end_time = *((u32*)(Data + sizeof(u32)));
        u16 start_char = *((u16*)(Data + 2 * sizeof(u32)));
        u16 end_char = *((u16*)(Data + 2 * sizeof(u32) + sizeof(u16)));
        gf_isom_text_set_karaoke_segment(sample, end_time, start_char, end_char);
    }

    free_sample(sample);
    return 0;
}