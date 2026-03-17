// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_text_reset_styles at tx3g.c:612:8 in isomedia.h
// gf_isom_text_sample_write_bs at tx3g.c:440:8 in isomedia.h
// gf_isom_text_set_box at tx3g.c:384:8 in isomedia.h
// gf_isom_text_set_wrap at tx3g.c:411:8 in isomedia.h
// gf_isom_text_reset at tx3g.c:636:8 in isomedia.h
// gf_isom_text_add_style at tx3g.c:290:8 in isomedia.h
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Define the structure as the compiler needs its complete definition
struct _3gpp_text_sample {
    char *text;
    u32 len;
    void *styles; // Use void* for unknown types
    void *highlight_color;
    void *scroll_delay;
    void *box;
    void *wrap;
    Bool is_forced;
    GF_List *others;
    void *cur_karaoke;
};

// Define a minimal GF_BitStream structure
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
    sample->len = (u32)Size;
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
    GF_BitStream *bs = (GF_BitStream *)malloc(sizeof(GF_BitStream));
    if (!bs) return NULL;

    bs->stream = fopen("./dummy_file", "wb+");
    if (!bs->stream) {
        free(bs);
        return NULL;
    }

    bs->original = NULL;
    bs->size = 0;
    bs->position = 0;
    bs->current = 0;
    bs->nbBits = 0;
    bs->bsmode = 0;
    bs->EndOfStream = NULL;
    bs->par = NULL;
    bs->cache_write = NULL;
    bs->cache_write_size = 0;
    bs->buffer_written = 0;
    bs->remove_emul_prevention_byte = 0;
    bs->nb_zeros = 0;
    bs->nb_removed = 0;
    bs->on_block_out = NULL;
    bs->usr_data = NULL;
    bs->bytes_out = 0;
    bs->prevent_dispatch = 0;
    bs->cookie = 0;
    bs->cache_read = NULL;
    bs->cache_read_size = 0;
    bs->cache_read_pos = 0;
    bs->cache_read_alloc = 0;
    bs->on_log = NULL;
    bs->log_udta = NULL;
    bs->total_bits_read = 0;
    bs->overflow_state = 0;
    bs->o_size = 0;

    return bs;
}

int LLVMFuzzerTestOneInput_290(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0; // Ensure there is enough data for the operations

    GF_TextSample *sample = create_text_sample(Data, Size);
    if (!sample) return 0;

    GF_BitStream *bs = create_bitstream();
    if (!bs) {
        free(sample->text);
        free(sample);
        return 0;
    }

    gf_isom_text_reset_styles(sample);
    gf_isom_text_sample_write_bs(sample, bs);
    gf_isom_text_set_box(sample, (s16)(Data[0] % 128), (s16)(Data[1] % 128), (s16)(Data[2] % 128), (s16)(Data[3] % 128));
    gf_isom_text_set_wrap(sample, Data[4] % 2);
    gf_isom_text_reset(sample);

    GF_StyleRecord style;
    gf_isom_text_add_style(sample, &style);

    fclose(bs->stream);
    free(bs);
    free(sample->text);
    free(sample);

    return 0;
}