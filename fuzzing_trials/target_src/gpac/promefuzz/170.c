// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_delete_text_sample at tx3g.c:646:6 in isomedia.h
// gf_isom_text_reset at tx3g.c:636:8 in isomedia.h
// gf_isom_text_reset_styles at tx3g.c:612:8 in isomedia.h
// gf_isom_text_add_highlight at tx3g.c:306:8 in isomedia.h
// gf_isom_text_add_hyperlink at tx3g.c:370:8 in isomedia.h
// gf_isom_text_add_blink at tx3g.c:399:8 in isomedia.h
// gf_isom_text_set_karaoke_segment at tx3g.c:345:8 in isomedia.h
// gf_isom_new_text_sample at tx3g.c:602:16 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_TextSample* create_text_sample() {
    GF_TextSample *sample = gf_isom_new_text_sample();
    return sample;
}

static void destroy_text_sample(GF_TextSample *sample) {
    if (sample) {
        gf_isom_delete_text_sample(sample);
    }
}

int LLVMFuzzerTestOneInput_170(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_TextSample *sample = create_text_sample();
    if (!sample) return 0;

    gf_isom_text_reset(sample);
    gf_isom_text_reset_styles(sample);

    if (Size >= 4) {
        u16 start_char = Data[0];
        u16 end_char = Data[1];
        gf_isom_text_add_highlight(sample, start_char, end_char);
    }

    if (Size >= 6) {
        size_t url_len = Size - 2 > 256 ? 256 : Size - 2;  // Limit URL length to avoid excessive allocation
        char *url = (char *)malloc(url_len + 1);
        if (url) {
            memcpy(url, &Data[2], url_len);
            url[url_len] = '\0';  // Null-terminate

            size_t alt_len = Size - 3 > 256 ? 256 : Size - 3;  // Limit altString length
            char *altString = (char *)malloc(alt_len + 1);
            if (altString) {
                memcpy(altString, &Data[3], alt_len);
                altString[alt_len] = '\0';  // Null-terminate

                u16 start_char = Data[4];
                u16 end_char = Data[5];
                gf_isom_text_add_hyperlink(sample, url, altString, start_char, end_char);

                free(altString);
            }
            free(url);
        }
    }

    if (Size >= 8) {
        u16 start_char = Data[6];
        u16 end_char = Data[7];
        gf_isom_text_add_blink(sample, start_char, end_char);
    }

    if (Size >= 12) {
        u32 end_time = *((u32 *)&Data[8]);
        u16 start_char = Data[10];
        u16 end_char = Data[11];
        gf_isom_text_set_karaoke_segment(sample, end_time, start_char, end_char);
    }

    destroy_text_sample(sample);
    return 0;
}