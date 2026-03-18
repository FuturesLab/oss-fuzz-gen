// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_has_time_offset at isom_read.c:1868:5 in isomedia.h
// gf_isom_get_pssh_count at isom_read.c:5559:5 in isomedia.h
// gf_isom_set_next_moof_number at movie_fragments.c:3474:6 in isomedia.h
// gf_isom_segment_get_fragment_count at isom_read.c:864:5 in isomedia.h
// gf_isom_get_track_count at isom_read.c:783:5 in isomedia.h
// gf_isom_get_track_flags at isom_read.c:1064:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
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
        remove("./dummy_file");
    }
}

int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure enough data for track number and moof value

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = Data[0] % 256;
    u32 moofNumber = Data[1] % 256;

    // Fuzz gf_isom_has_time_offset
    u32 offset_result = gf_isom_has_time_offset(isom_file, trackNumber);

    // Fuzz gf_isom_get_pssh_count
    u32 pssh_count = gf_isom_get_pssh_count(isom_file);

    // Fuzz gf_isom_set_next_moof_number
    gf_isom_set_next_moof_number(isom_file, moofNumber);

    // Fuzz gf_isom_segment_get_fragment_count
    u32 fragment_count = gf_isom_segment_get_fragment_count(isom_file);

    // Fuzz gf_isom_get_track_count
    u32 track_count = gf_isom_get_track_count(isom_file);

    // Fuzz gf_isom_get_track_flags
    u32 track_flags = gf_isom_get_track_flags(isom_file, trackNumber);

    // Clean up
    cleanup_iso_file(isom_file);

    return 0;
}