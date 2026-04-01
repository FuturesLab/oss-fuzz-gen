// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_reset_seq_num at isom_read.c:4997:6 in isomedia.h
// gf_isom_flush_fragments at movie_fragments.c:1468:8 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_reset_fragment_info at isom_read.c:4976:6 in isomedia.h
// gf_isom_is_smooth_streaming_moov at isom_read.c:5848:6 in isomedia.h
// gf_isom_set_progress_callback at isom_write.c:8548:6 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void dummy_progress_callback(void *udta, u64 nb_done, u64 nb_total) {
    // Dummy progress callback function
}

int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *)) return 0;

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    // Write dummy data to a file if needed
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Invoke gf_isom_reset_seq_num
    gf_isom_reset_seq_num(isom_file);

    // Invoke gf_isom_flush_fragments
    Bool last_segment = (Bool)(Data[0] % 2);
    gf_isom_flush_fragments(isom_file, last_segment);

    // Invoke gf_isom_delete
    gf_isom_delete(isom_file);

    // Re-open the file for further operations
    isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    // Invoke gf_isom_reset_fragment_info
    Bool keep_sample_count = (Bool)(Data[1] % 2);
    gf_isom_reset_fragment_info(isom_file, keep_sample_count);

    // Invoke gf_isom_is_smooth_streaming_moov
    Bool is_smooth = gf_isom_is_smooth_streaming_moov(isom_file);

    // Invoke gf_isom_set_progress_callback
    gf_isom_set_progress_callback(isom_file, dummy_progress_callback, NULL);

    // Clean up
    gf_isom_delete(isom_file);

    return 0;
}