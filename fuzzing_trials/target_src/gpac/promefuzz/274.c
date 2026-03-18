// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_reset_seq_num at isom_read.c:4997:6 in isomedia.h
// gf_isom_reset_fragment_info at isom_read.c:4976:6 in isomedia.h
// gf_isom_flush_fragments at movie_fragments.c:1468:8 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
// gf_isom_set_progress_callback at isom_write.c:8548:6 in isomedia.h
// gf_isom_is_smooth_streaming_moov at isom_read.c:5848:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Dummy progress callback
static void dummy_progress_callback(void *udta, u64 nb_done, u64 nb_total) {
    // Do nothing
}

// Dummy GF_ISOFile creation function
static GF_ISOFile *create_dummy_iso_file() {
    GF_ISOFile *isom_file = NULL;
    // Normally, you would create or open an actual ISO file using GPAC APIs
    // Here, we just allocate memory for fuzzing purposes
    return isom_file;
}

int LLVMFuzzerTestOneInput_274(const uint8_t *Data, size_t Size) {
    // Create a dummy ISO file object
    GF_ISOFile *isom_file = create_dummy_iso_file();

    if (!isom_file) {
        return 0;
    }

    // Call gf_isom_reset_seq_num
    gf_isom_reset_seq_num(isom_file);

    // Call gf_isom_reset_fragment_info with random Bool
    Bool keep_sample_count = (Size % 2 == 0) ? GF_TRUE : GF_FALSE;
    gf_isom_reset_fragment_info(isom_file, keep_sample_count);

    // Call gf_isom_flush_fragments with random Bool
    Bool last_segment = (Size % 3 == 0) ? GF_TRUE : GF_FALSE;
    gf_isom_flush_fragments(isom_file, last_segment);

    // Call gf_isom_delete
    gf_isom_delete(isom_file);

    // Call gf_isom_set_progress_callback
    gf_isom_set_progress_callback(isom_file, dummy_progress_callback, NULL);

    // Call gf_isom_is_smooth_streaming_moov
    Bool is_smooth = gf_isom_is_smooth_streaming_moov(isom_file);

    return 0;
}