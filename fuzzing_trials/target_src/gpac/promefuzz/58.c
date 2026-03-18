// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_text_reset_styles at tx3g.c:612:8 in isomedia.h
// gf_isom_text_set_highlight_color at tx3g.c:321:8 in isomedia.h
// gf_isom_text_reset at tx3g.c:636:8 in isomedia.h
// gf_isom_text_add_text at tx3g.c:259:8 in isomedia.h
// gf_isom_text_add_karaoke at tx3g.c:335:8 in isomedia.h
// gf_isom_text_set_scroll_delay at tx3g.c:358:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

// Assuming the size of GF_TextSample is known or obtained from the library
#define TEXT_SAMPLE_SIZE 128  // Placeholder size, should be replaced with actual size

static GF_TextSample* create_text_sample() {
    GF_TextSample *sample = (GF_TextSample *) malloc(TEXT_SAMPLE_SIZE);
    if (!sample) return NULL;
    memset(sample, 0, TEXT_SAMPLE_SIZE);
    return sample;
}

static void destroy_text_sample(GF_TextSample *sample) {
    if (!sample) return;
    // Assuming isomedia provides a function to properly clean up a GF_TextSample
    free(sample);
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 12) return 0; // Ensure enough data for u32 values and text

    GF_TextSample *sample = create_text_sample();
    if (!sample) return 0;

    // Extract values from Data
    u32 argb_color = *(u32 *)Data;
    u32 scroll_delay = *(u32 *)(Data + 4);
    u32 karaoke_start_time = *(u32 *)(Data + 8);
    char *text_data = (char *)(Data + 12);
    u32 text_len = Size > 12 ? Size - 12 : 0;

    // Invoke API functions
    gf_isom_text_reset_styles(sample);
    gf_isom_text_set_highlight_color(sample, argb_color);
    gf_isom_text_reset(sample);
    gf_isom_text_add_text(sample, text_data, text_len);
    gf_isom_text_add_karaoke(sample, karaoke_start_time);
    gf_isom_text_set_scroll_delay(sample, scroll_delay);

    // Clean up
    destroy_text_sample(sample);
    return 0;
}