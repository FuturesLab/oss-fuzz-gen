// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_enum_track_references at isom_read.c:1219:22 in isomedia.h
// gf_isom_get_mpeg4_subtype at isom_read.c:1671:5 in isomedia.h
// gf_isom_is_track_referenced at isom_read.c:1316:5 in isomedia.h
// gf_isom_has_track_reference at isom_read.c:1295:5 in isomedia.h
// gf_isom_get_generic_sample_description at isom_read.c:3714:30 in isomedia.h
// gf_isom_get_media_timescale at isom_read.c:1459:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int LLVMFuzzerTestOneInput_172(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u32 idx = Data[1];
    u32 referenceType = 0;
    u32 referenceCount = 0;

    const GF_ISOTrackID *trackIDs = gf_isom_enum_track_references(isom_file, trackNumber, idx, &referenceType, &referenceCount);
    if (trackIDs) {
        free((void *)trackIDs);
    }

    u32 sampleDescriptionIndex = Data[2];
    u32 mpeg4_subtype = gf_isom_get_mpeg4_subtype(isom_file, trackNumber, sampleDescriptionIndex);

    u32 referenceTypeCheck = Data[3];
    u32 referencingTrack = gf_isom_is_track_referenced(isom_file, trackNumber, referenceTypeCheck);

    GF_ISOTrackID refTrackID = Data[3];
    u32 referenceIndex = gf_isom_has_track_reference(isom_file, trackNumber, referenceTypeCheck, refTrackID);

    GF_GenericSampleDescription *sampleDesc = gf_isom_get_generic_sample_description(isom_file, trackNumber, sampleDescriptionIndex);
    if (sampleDesc) {
        free(sampleDesc);
    }

    u32 mediaTimescale = gf_isom_get_media_timescale(isom_file, trackNumber);

    cleanup_iso_file(isom_file);
    return 0;
}