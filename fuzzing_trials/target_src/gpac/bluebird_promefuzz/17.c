#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_TextSample* create_text_sample() {
    GF_TextSample *tx_samp = gf_isom_new_text_sample();
    return tx_samp;
}

static void free_text_sample(GF_TextSample *tx_samp) {
    if (!tx_samp) return;
    gf_isom_delete_text_sample(tx_samp);
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    GF_TextSample *tx_samp = create_text_sample();
    if (!tx_samp) return 0;

    u32 end_time = *(u32 *)Data;
    u16 start_char = *(u16 *)(Data + sizeof(u32));
    u16 end_char = *(u16 *)(Data + sizeof(u32) + sizeof(u16));
    u32 argb = *(u32 *)(Data + sizeof(u32) + sizeof(u16) * 2);
    u32 text_len = (Size - sizeof(u32) * 4) > 0 ? (Size - sizeof(u32) * 4) : 0;
    char *text_data = (char *)(Data + sizeof(u32) * 4);

    gf_isom_text_set_karaoke_segment(tx_samp, end_time, start_char, end_char);
    gf_isom_text_set_highlight_color(tx_samp, argb);
    gf_isom_text_add_text(tx_samp, text_data, text_len);
    gf_isom_text_sample_size(tx_samp);
    gf_isom_text_add_karaoke(tx_samp, end_time);
    gf_isom_text_set_scroll_delay(tx_samp, end_time);

    free_text_sample(tx_samp);
    return 0;
}