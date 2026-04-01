// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_text_sample_write_bs at tx3g.c:440:8 in isomedia.h
// gf_isom_text_add_style at tx3g.c:290:8 in isomedia.h
// gf_isom_text_set_forced at tx3g.c:423:8 in isomedia.h
// gf_isom_text_set_box at tx3g.c:384:8 in isomedia.h
// gf_isom_text_reset at tx3g.c:636:8 in isomedia.h
// gf_isom_text_reset_styles at tx3g.c:612:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Define the structs as they are incomplete in the headers
struct _3gpp_text_sample {
    char *text;
    u32 len;
    void *styles;
    void *highlight_color;
    void *scroll_delay;
    void *box;
    void *wrap;
    Bool is_forced;
    void *others;
    void *cur_karaoke;
};

struct __tag_bitstream {
    FILE *stream;
    char *original;
    u64 size;
    u64 position;
    u32 current;
    u32 nbBits;
    u32 bsmode;
    void (*EndOfStream)(void *par);
    void *par;
    char *cache_write;
    u32 cache_write_size, buffer_written;
    Bool remove_emul_prevention_byte;
    u32 nb_zeros, nb_removed;
    GF_Err (*on_block_out)(void *cbk, u8 *data, u32 block_size);
    void *usr_data;
    u64 bytes_out;
    u32 prevent_dispatch;
    u64 cookie;
    u8 *cache_read;
    u32 cache_read_size, cache_read_pos, cache_read_alloc;
    void (*on_log)(void *udta, const char *field_name, u32 nb_bits, u64 field_val, s32 idx1, s32 idx2, s32 idx3);
    void *log_udta;
    u32 total_bits_read;
    u32 overflow_state;
    u64 o_size;
#ifdef GPAC_HAS_FD
    int fd;
#endif
};

static GF_TextSample* create_text_sample() {
    GF_TextSample* sample = (GF_TextSample*)malloc(sizeof(GF_TextSample));
    if (sample) {
        memset(sample, 0, sizeof(GF_TextSample));
    }
    return sample;
}

static GF_BitStream* create_bitstream() {
    GF_BitStream* bs = (GF_BitStream*)malloc(sizeof(GF_BitStream));
    if (bs) {
        memset(bs, 0, sizeof(GF_BitStream));
        bs->stream = fopen("./dummy_file", "wb+");
    }
    return bs;
}

static void cleanup_text_sample(GF_TextSample* sample) {
    if (sample) {
        free(sample->text);
        free(sample);
    }
}

static void cleanup_bitstream(GF_BitStream* bs) {
    if (bs) {
        if (bs->stream) {
            fclose(bs->stream);
        }
        free(bs);
    }
}

int LLVMFuzzerTestOneInput_320(const uint8_t *Data, size_t Size) {
    GF_TextSample* sample = create_text_sample();
    GF_BitStream* bs = create_bitstream();
    if (!sample || !bs) {
        cleanup_text_sample(sample);
        cleanup_bitstream(bs);
        return 0;
    }

    // Fuzz gf_isom_text_reset
    gf_isom_text_reset(sample);

    // Fuzz gf_isom_text_reset_styles
    gf_isom_text_reset_styles(sample);

    // Fuzz gf_isom_text_sample_write_bs
    gf_isom_text_sample_write_bs(sample, bs);

    // Fuzz gf_isom_text_add_style
    GF_StyleRecord* style = (GF_StyleRecord*)malloc(sizeof(GF_StyleRecord));
    if (style) {
        memset(style, 0, sizeof(GF_StyleRecord));
        gf_isom_text_add_style(sample, style);
        free(style);
    }

    // Fuzz gf_isom_text_set_forced
    gf_isom_text_set_forced(sample, (Bool)(Data[0] % 2));

    // Fuzz gf_isom_text_set_box
    if (Size >= 8) {
        s16 top = *(s16*)(Data + 0);
        s16 left = *(s16*)(Data + 2);
        s16 bottom = *(s16*)(Data + 4);
        s16 right = *(s16*)(Data + 6);
        gf_isom_text_set_box(sample, top, left, bottom, right);
    }

    cleanup_text_sample(sample);
    cleanup_bitstream(bs);

    return 0;
}