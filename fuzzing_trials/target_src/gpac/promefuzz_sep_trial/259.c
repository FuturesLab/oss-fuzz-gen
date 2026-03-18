// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_fragmented_duration at isom_read.c:5409:5 in isomedia.h
// gf_isom_get_duration at isom_read.c:971:5 in isomedia.h
// gf_isom_get_track_duration_orig at isom_read.c:1092:5 in isomedia.h
// gf_isom_get_track_duration at isom_read.c:1076:5 in isomedia.h
// gf_isom_get_smooth_next_tfdt at isom_read.c:5835:5 in isomedia.h
// gf_isom_get_original_duration at isom_read.c:986:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_259(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    // Fuzz gf_isom_get_fragmented_duration
    u64 fragmented_duration = gf_isom_get_fragmented_duration(isom_file);

    // Fuzz gf_isom_get_duration
    u64 duration = gf_isom_get_duration(isom_file);

    // Fuzz gf_isom_get_track_duration_orig
    for (u32 trackNumber = 0; trackNumber < 5; trackNumber++) {
        u64 track_duration_orig = gf_isom_get_track_duration_orig(isom_file, trackNumber);
    }

    // Fuzz gf_isom_get_track_duration
    for (u32 trackNumber = 0; trackNumber < 5; trackNumber++) {
        u64 track_duration = gf_isom_get_track_duration(isom_file, trackNumber);
    }

    // Fuzz gf_isom_get_smooth_next_tfdt
    for (u32 trackNumber = 0; trackNumber < 5; trackNumber++) {
        u64 smooth_next_tfdt = gf_isom_get_smooth_next_tfdt(isom_file, trackNumber);
    }

    // Fuzz gf_isom_get_original_duration
    u64 original_duration = gf_isom_get_original_duration(isom_file);

    cleanup_iso_file(isom_file);
    return 0;
}