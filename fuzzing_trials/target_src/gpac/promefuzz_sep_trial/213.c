// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_keep_utc_times at isom_read.c:5543:6 in isomedia.h
// gf_isom_has_keep_utc_times at isom_read.c:5550:6 in isomedia.h
// gf_isom_disable_inplace_rewrite at isom_write.c:9058:6 in isomedia.h
// gf_isom_has_movie at isom_read.c:835:6 in isomedia.h
// gf_isom_reset_sample_count at isom_read.c:5005:6 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "isomedia.h"

#define GF_TRUE 1
#define GF_FALSE 0

int LLVMFuzzerTestOneInput_213(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy GF_ISOFile pointer
    GF_ISOFile* isofile = NULL;

    // Randomly decide to keep UTC times
    Bool keep_utc = Data[0] % 2 == 0 ? GF_TRUE : GF_FALSE;
    gf_isom_keep_utc_times(isofile, keep_utc);

    // Check if UTC keeping is enabled
    Bool utc_enabled = gf_isom_has_keep_utc_times(isofile);

    // Randomly decide to disable in-place rewrite
    if (Size > 1 && Data[1] % 2 == 0) {
        gf_isom_disable_inplace_rewrite(isofile);
    }

    // Check if the file has a movie
    Bool has_movie = gf_isom_has_movie(isofile);

    // Reset sample count
    gf_isom_reset_sample_count(isofile);

    // Clean up
    gf_isom_delete(isofile);

    return 0;
}