// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_text_reset at tx3g.c:636:8 in isomedia.h
// gf_isom_text_reset_styles at tx3g.c:612:8 in isomedia.h
// gf_isom_text_sample_write_bs at tx3g.c:440:8 in isomedia.h
// gf_isom_text_add_style at tx3g.c:290:8 in isomedia.h
// gf_isom_text_set_forced at tx3g.c:423:8 in isomedia.h
// gf_isom_text_set_wrap at tx3g.c:411:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Forward declaration of unknown types to avoid compilation errors
typedef struct GF_TextStyleBox GF_TextStyleBox;
typedef struct GF_TextHighlightColorBox GF_TextHighlightColorBox;
typedef struct GF_TextScrollDelayBox GF_TextScrollDelayBox;
typedef struct GF_TextBoxBox GF_TextBoxBox;
typedef struct GF_TextWrapBox GF_TextWrapBox;
typedef struct GF_TextKaraokeBox GF_TextKaraokeBox;
typedef struct _tag_array GF_List;

// Define the structure of GF_TextSample since it is a forward declaration
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

static GF_TextSample* create_dummy_text_sample() {
    GF_TextSample *sample = (GF_TextSample *)malloc(sizeof(GF_TextSample));
    if (!sample) return NULL;
    sample->text = strdup("Sample text");
    sample->len = sample->text ? strlen(sample->text) : 0;
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

static GF_StyleRecord* create_dummy_style_record() {
    GF_StyleRecord *style = (GF_StyleRecord *)malloc(sizeof(GF_StyleRecord));
    return style;
}

static GF_BitStream* create_dummy_bitstream() {
    GF_BitStream *bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
    return bs;
}

int LLVMFuzzerTestOneInput_260(const uint8_t *Data, size_t Size) {
    GF_TextSample *sample = create_dummy_text_sample();
    if (!sample) return 0;

    GF_StyleRecord *style = create_dummy_style_record();
    GF_BitStream *bs = create_dummy_bitstream();

    if (sample) {
        gf_isom_text_reset(sample);
        gf_isom_text_reset_styles(sample);

        if (bs) {
            gf_isom_text_sample_write_bs(sample, bs);
        }

        if (style) {
            gf_isom_text_add_style(sample, style);
        }

        gf_isom_text_set_forced(sample, Data[0] % 2);
        gf_isom_text_set_wrap(sample, Data[0] % 2);
    }

    if (sample) {
        free(sample->text);
        free(sample);
    }

    if (style) {
        free(style);
    }

    if (bs) {
        gf_bs_del(bs);
    }

    return 0;
}