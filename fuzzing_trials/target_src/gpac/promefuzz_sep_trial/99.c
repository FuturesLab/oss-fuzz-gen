// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_delete_text_sample at tx3g.c:646:6 in isomedia.h
// gf_isom_text_sample_size at tx3g.c:498:5 in isomedia.h
// gf_isom_text_add_karaoke at tx3g.c:335:8 in isomedia.h
// gf_isom_new_text_sample at tx3g.c:602:16 in isomedia.h
// gf_isom_text_set_highlight_color at tx3g.c:321:8 in isomedia.h
// gf_isom_text_set_scroll_delay at tx3g.c:358:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void fuzz_gf_isom_delete_text_sample(GF_TextSample *tx_samp) {
    gf_isom_delete_text_sample(tx_samp);
}

static u32 fuzz_gf_isom_text_sample_size(GF_TextSample *tx_samp) {
    return gf_isom_text_sample_size(tx_samp);
}

static GF_Err fuzz_gf_isom_text_add_karaoke(GF_TextSample *tx_samp, u32 start_time) {
    return gf_isom_text_add_karaoke(tx_samp, start_time);
}

static GF_TextSample* fuzz_gf_isom_new_text_sample() {
    return gf_isom_new_text_sample();
}

static GF_Err fuzz_gf_isom_text_set_highlight_color(GF_TextSample *tx_samp, u32 argb) {
    return gf_isom_text_set_highlight_color(tx_samp, argb);
}

static GF_Err fuzz_gf_isom_text_set_scroll_delay(GF_TextSample *tx_samp, u32 scroll_delay) {
    return gf_isom_text_set_scroll_delay(tx_samp, scroll_delay);
}

int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(u32)) return 0;

    u32 start_time = *((u32 *)Data);
    u32 argb = *((u32 *)(Data + sizeof(u32)));
    u32 scroll_delay = *((u32 *)(Data + 2 * sizeof(u32)));

    GF_TextSample *tx_samp = fuzz_gf_isom_new_text_sample();
    if (!tx_samp) return 0;

    fuzz_gf_isom_text_add_karaoke(tx_samp, start_time);
    fuzz_gf_isom_text_set_highlight_color(tx_samp, argb);
    fuzz_gf_isom_text_set_scroll_delay(tx_samp, scroll_delay);

    u32 size = fuzz_gf_isom_text_sample_size(tx_samp);

    (void)size; // Suppress unused variable warning

    fuzz_gf_isom_delete_text_sample(tx_samp);

    return 0;
}