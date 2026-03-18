// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_keep_utc_times at isom_read.c:5543:6 in isomedia.h
// gf_isom_has_movie at isom_read.c:835:6 in isomedia.h
// gf_isom_has_keep_utc_times at isom_read.c:5550:6 in isomedia.h
// gf_isom_disable_inplace_rewrite at isom_write.c:9058:6 in isomedia.h
// gf_isom_reset_sample_count at isom_read.c:5005:6 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_222(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file to simulate the presence of an ISO file
    FILE *dummyFile = fopen("./dummy_file", "wb");
    if (!dummyFile) return 0;
    fwrite(Data, 1, Size, dummyFile);
    fclose(dummyFile);

    // Open the dummy ISO file
    GF_ISOFile *isofile = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isofile) return 0;

    Bool keep_utc = (Bool)(Data[0] % 2);
    gf_isom_keep_utc_times(isofile, keep_utc);

    Bool has_movie = gf_isom_has_movie(isofile);
    (void)has_movie; // Suppress unused variable warning

    Bool has_keep_utc = gf_isom_has_keep_utc_times(isofile);
    (void)has_keep_utc; // Suppress unused variable warning

    gf_isom_disable_inplace_rewrite(isofile);

    gf_isom_reset_sample_count(isofile);

    gf_isom_delete(isofile);

    return 0;
}