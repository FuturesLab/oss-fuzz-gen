// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_fragment_set_sample_flags at movie_fragments.c:3395:8 in isomedia.h
// gf_isom_set_timescale at isom_write.c:451:8 in isomedia.h
// gf_isom_set_brand_info at isom_write.c:3520:8 in isomedia.h
// gf_isom_rewrite_track_dependencies at isom_write.c:5120:8 in isomedia.h
// gf_isom_set_fragment_original_duration at movie_fragments.c:3171:8 in isomedia.h
// gf_isom_set_track_reference at isom_write.c:4967:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    // Since GF_ISOFile is a forward-declared type, we cannot allocate it directly.
    // For fuzzing purposes, we assume the library provides a function to create an ISO file.
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Ensure there is enough data to read

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    u32 trackID = Data[0];
    u32 is_leading = Data[1] & 0x1;
    u32 dependsOn = (Data[1] >> 1) & 0x3;
    u32 dependedOn = (Data[1] >> 3) & 0x3;
    u32 redundant = (Data[1] >> 5) & 0x1;

    gf_isom_fragment_set_sample_flags(isom_file, trackID, is_leading, dependsOn, dependedOn, redundant);

    u32 timeScale = *(u32 *)(Data + 4);
    gf_isom_set_timescale(isom_file, timeScale);

    u32 MajorBrand = *(u32 *)(Data + 8);
    u32 MinorVersion = *(u32 *)(Data + 12);
    gf_isom_set_brand_info(isom_file, MajorBrand, MinorVersion);

    u32 trackNumber = *(u32 *)(Data + 4);
    gf_isom_rewrite_track_dependencies(isom_file, trackNumber);

    u32 orig_dur = *(u32 *)(Data + 8);
    u32 elapsed_dur = *(u32 *)(Data + 12);
    gf_isom_set_fragment_original_duration(isom_file, trackID, orig_dur, elapsed_dur);

    u32 referenceType = *(u32 *)(Data + 8);
    u32 ReferencedTrackID = *(u32 *)(Data + 12);
    gf_isom_set_track_reference(isom_file, trackNumber, referenceType, ReferencedTrackID);

    cleanup_iso_file(isom_file);
    return 0;
}