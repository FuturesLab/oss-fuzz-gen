// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_clean_aperture at isom_read.c:6405:8 in isomedia.h
// gf_isom_fragment_add_sample_references at movie_fragments.c:3537:8 in isomedia.h
// gf_isom_get_reference at isom_read.c:1237:8 in isomedia.h
// gf_isom_set_sample_references at isom_write.c:9510:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_get_sample_flags at isom_read.c:1913:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
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

static void fuzz_gf_isom_get_clean_aperture(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;
    
    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 cleanApertureWidthN, cleanApertureWidthD, cleanApertureHeightN, cleanApertureHeightD;
    s32 horizOffN, vertOffN;
    u32 horizOffD, vertOffD;

    gf_isom_get_clean_aperture(isom_file, trackNumber, sampleDescriptionIndex, 
                               &cleanApertureWidthN, &cleanApertureWidthD, 
                               &cleanApertureHeightN, &cleanApertureHeightD, 
                               &horizOffN, &horizOffD, 
                               &vertOffN, &vertOffD);
}

static void fuzz_gf_isom_fragment_add_sample_references(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 12) return;

    GF_ISOTrackID TrackID = *(GF_ISOTrackID *)Data;
    s32 refID = *(s32 *)(Data + 4);
    u32 nb_refs = *(u32 *)(Data + 8);

    if (Size < 12 + nb_refs * sizeof(s32)) return;
    
    s32 *refs = (s32 *)(Data + 12);

    gf_isom_fragment_add_sample_references(isom_file, TrackID, refID, nb_refs, refs);
}

static void fuzz_gf_isom_get_reference(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 12) return;

    u32 trackNumber = *(u32 *)Data;
    u32 referenceType = *(u32 *)(Data + 4);
    u32 referenceIndex = *(u32 *)(Data + 8);
    u32 refTrack;

    gf_isom_get_reference(isom_file, trackNumber, referenceType, referenceIndex, &refTrack);
}

static void fuzz_gf_isom_set_sample_references(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 16) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)(Data + 4);
    s32 ID = *(s32 *)(Data + 8);
    u32 nb_refs = *(u32 *)(Data + 12);

    if (Size < 16 + nb_refs * sizeof(s32)) return;

    s32 *refs = (s32 *)(Data + 16);

    gf_isom_set_sample_references(isom_file, trackNumber, sampleNumber, ID, nb_refs, refs);
}

static void fuzz_gf_isom_set_track_id(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;

    u32 trackNumber = *(u32 *)Data;
    GF_ISOTrackID trackID = *(GF_ISOTrackID *)(Data + 4);

    gf_isom_set_track_id(isom_file, trackNumber, trackID);
}

static void fuzz_gf_isom_get_sample_flags(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 12) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)(Data + 4);
    u32 is_leading, dependsOn, dependedOn, redundant;

    gf_isom_get_sample_flags(isom_file, trackNumber, sampleNumber, &is_leading, &dependsOn, &dependedOn, &redundant);
}

int LLVMFuzzerTestOneInput_174(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);

    if (!isom_file) return 0;

    fuzz_gf_isom_get_clean_aperture(isom_file, Data, Size);
    fuzz_gf_isom_fragment_add_sample_references(isom_file, Data, Size);
    fuzz_gf_isom_get_reference(isom_file, Data, Size);
    fuzz_gf_isom_set_sample_references(isom_file, Data, Size);
    fuzz_gf_isom_set_track_id(isom_file, Data, Size);
    fuzz_gf_isom_get_sample_flags(isom_file, Data, Size);

    gf_isom_close(isom_file);
    return 0;
}