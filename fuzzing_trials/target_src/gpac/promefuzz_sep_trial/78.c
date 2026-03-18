// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_freeze_order at isom_read.c:76:8 in isomedia.h
// gf_isom_update_duration at isom_write.c:8330:8 in isomedia.h
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_start_fragment at movie_fragments.c:2583:8 in isomedia.h
// gf_isom_set_timescale at isom_write.c:451:8 in isomedia.h
// gf_isom_can_access_movie at isom_write.c:34:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    // Check if the input size is sufficient
    if (Size < 1) return 0;

    // Simulate an ISO file object
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(isom_file);

    // Fuzz gf_isom_update_duration
    gf_isom_update_duration(isom_file);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(isom_file);

    // Fuzz gf_isom_start_fragment with random moof_first flag
    GF_ISOStartFragmentFlags moof_first = (GF_ISOStartFragmentFlags) (Data[0] % 2);
    gf_isom_start_fragment(isom_file, moof_first);

    // Fuzz gf_isom_set_timescale with a random timescale
    u32 timescale = (Size > 4) ? *(u32 *)(Data + 1) : 1000;
    gf_isom_set_timescale(isom_file, timescale);

    // Fuzz gf_isom_can_access_movie with random mode
    GF_ISOOpenMode mode = (GF_ISOOpenMode) (Data[0] % 3);
    gf_isom_can_access_movie(isom_file, mode);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}