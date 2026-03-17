#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

// Forward declare the structures since their definitions are not provided
typedef struct GF_TextStyleBox GF_TextStyleBox;
typedef struct GF_TextHighlightColorBox GF_TextHighlightColorBox;
typedef struct GF_TextScrollDelayBox GF_TextScrollDelayBox;
typedef struct GF_TextBoxBox GF_TextBoxBox;
typedef struct GF_TextWrapBox GF_TextWrapBox;
typedef struct GF_TextKaraokeBox GF_TextKaraokeBox;
typedef struct _tag_array GF_List;

// Define the complete structure for GF_TextSample as per the library's internal implementation
typedef struct _3gpp_text_sample {
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
} GF_TextSample;

static GF_TextSample* create_text_sample(const uint8_t *Data, size_t Size) {
    GF_TextSample *sample = (GF_TextSample *)malloc(sizeof(GF_TextSample));
    if (!sample) return NULL;

    sample->text = (char *)malloc(Size + 1);
    if (!sample->text) {
        free(sample);
        return NULL;
    }
    memcpy(sample->text, Data, Size);
    sample->text[Size] = '\0';
    sample->len = Size;

    sample->styles = NULL;
    sample->highlight_color = NULL;
    sample->scroll_delay = NULL;
    sample->box = NULL;
    sample->wrap = NULL;
    sample->is_forced = 0;
    sample->others = NULL;
    sample->cur_karaoke = NULL;

    return sample;
}

static GF_BitStream* create_bitstream() {
    GF_BitStream *bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
    return bs;
}

static void cleanup_text_sample(GF_TextSample *sample) {
    if (!sample) return;
    if (sample->text) free(sample->text);
    free(sample);
}

static void cleanup_bitstream(GF_BitStream *bs) {
    if (!bs) return;
    gf_bs_del(bs);
}

int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    GF_TextSample *sample = create_text_sample(Data, Size);
    if (!sample) return 0;

    GF_BitStream *bs = create_bitstream();
    if (!bs) {
        cleanup_text_sample(sample);
        return 0;
    }

    // Fuzzing gf_isom_text_reset_styles
    gf_isom_text_reset_styles(sample);

    // Fuzzing gf_isom_text_sample_write_bs
    gf_isom_text_sample_write_bs(sample, bs);

    // Fuzzing gf_isom_text_set_wrap
    gf_isom_text_set_wrap(sample, Data[0] % 2);

    // Fuzzing gf_isom_text_set_forced
    gf_isom_text_set_forced(sample, Data[0] % 2);

    // Fuzzing gf_isom_text_reset
    gf_isom_text_reset(sample);

    // Fuzzing gf_isom_text_add_karaoke
    if (Size >= 4) {
        uint32_t start_time = *(uint32_t *)Data;
        gf_isom_text_add_karaoke(sample, start_time);
    }

    cleanup_text_sample(sample);
    cleanup_bitstream(bs);

    return 0;
}