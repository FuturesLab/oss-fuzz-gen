// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_highest_track_in_scalable_segment at isom_read.c:3640:15 in isomedia.h
// gf_isom_get_max_sample_delta at isom_read.c:2043:5 in isomedia.h
// gf_isom_has_track_reference at isom_read.c:1295:5 in isomedia.h
// gf_isom_av1_config_get at avc_ext.c:2605:15 in isomedia.h
// gf_isom_get_mpeg4_subtype at isom_read.c:1671:5 in isomedia.h
// gf_isom_enum_track_references at isom_read.c:1219:22 in isomedia.h
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

int LLVMFuzzerTestOneInput_306(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    // Prepare the environment
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 referenceType = *(u32 *)(Data + sizeof(u32));
    u32 refTrackID = *(u32 *)(Data + 2 * sizeof(u32));

    // Dummy file writing
    write_dummy_file(Data, Size);

    // Invoke the target functions
    gf_isom_get_highest_track_in_scalable_segment(isom_file, trackNumber);
    gf_isom_get_max_sample_delta(isom_file, trackNumber);
    gf_isom_has_track_reference(isom_file, trackNumber, referenceType, refTrackID);
    gf_isom_av1_config_get(isom_file, trackNumber, referenceType);
    gf_isom_get_mpeg4_subtype(isom_file, trackNumber, referenceType);

    u32 referenceTypeOut, referenceCountOut;
    gf_isom_enum_track_references(isom_file, trackNumber, 0, &referenceTypeOut, &referenceCountOut);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}