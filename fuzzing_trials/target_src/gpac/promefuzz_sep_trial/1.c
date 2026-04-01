// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_count at isom_read.c:1767:5 in isomedia.h
// gf_isom_get_constant_sample_duration at isom_read.c:1789:5 in isomedia.h
// gf_isom_get_avg_sample_delta at isom_read.c:2052:5 in isomedia.h
// gf_isom_get_sync_point_count at isom_read.c:2618:5 in isomedia.h
// gf_isom_get_nalu_length_field at isom_read.c:5918:5 in isomedia.h
// gf_isom_get_track_flags at isom_read.c:1064:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Create a dummy file to simulate an ISO file input
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file as a GF_ISOFile
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    // Extract trackNumber and sampleDescriptionIndex from input data
    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));

    // Call the target API functions with the initialized data
    u32 sample_count = gf_isom_get_sample_count(isom_file, trackNumber);
    u32 constant_sample_duration = gf_isom_get_constant_sample_duration(isom_file, trackNumber);
    u32 avg_sample_delta = gf_isom_get_avg_sample_delta(isom_file, trackNumber);
    u32 sync_point_count = gf_isom_get_sync_point_count(isom_file, trackNumber);
    u32 nalu_length_field = gf_isom_get_nalu_length_field(isom_file, trackNumber, sampleDescriptionIndex);
    u32 track_flags = gf_isom_get_track_flags(isom_file, trackNumber);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}