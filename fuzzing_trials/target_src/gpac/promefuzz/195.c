// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_max_sample_size at isom_read.c:2021:5 in isomedia.h
// gf_isom_get_max_sample_delta at isom_read.c:2043:5 in isomedia.h
// gf_isom_get_sync_point_count at isom_read.c:2618:5 in isomedia.h
// gf_isom_get_avg_sample_size at isom_read.c:2030:5 in isomedia.h
// gf_isom_get_edits_count at isom_read.c:2547:5 in isomedia.h
// gf_isom_get_mastering_display_colour_info at isom_read.c:6475:44 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* open_dummy_isofile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void close_isofile(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
        remove("./dummy_file");
    }
}

int LLVMFuzzerTestOneInput_195(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure we have enough data for a track number

    GF_ISOFile *isom_file = open_dummy_isofile(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);

    // Fuzz each target function with the dummy ISO file and trackNumber
    u32 max_sample_size = gf_isom_get_max_sample_size(isom_file, trackNumber);
    u32 max_sample_delta = gf_isom_get_max_sample_delta(isom_file, trackNumber);
    u32 sync_point_count = gf_isom_get_sync_point_count(isom_file, trackNumber);
    u32 avg_sample_size = gf_isom_get_avg_sample_size(isom_file, trackNumber);
    u32 edits_count = gf_isom_get_edits_count(isom_file, trackNumber);

    // For gf_isom_get_mastering_display_colour_info, we need a sample description index
    if (Size >= 8) {
        u32 sampleDescriptionIndex = *((u32 *)(Data + 4));
        const GF_MasteringDisplayColourVolumeInfo *colour_info =
            gf_isom_get_mastering_display_colour_info(isom_file, trackNumber, sampleDescriptionIndex);
    }

    close_isofile(isom_file);
    return 0;
}