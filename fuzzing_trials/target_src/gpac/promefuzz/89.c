// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_cts_to_dts_shift at isom_read.c:1885:5 in isomedia.h
// gf_isom_get_max_sample_delta at isom_read.c:2043:5 in isomedia.h
// gf_isom_get_constant_sample_size at isom_read.c:1780:5 in isomedia.h
// gf_isom_get_media_type at isom_read.c:1586:5 in isomedia.h
// gf_isom_has_track_reference at isom_read.c:1295:5 in isomedia.h
// gf_isom_get_max_sample_cts_offset at isom_read.c:2070:5 in isomedia.h
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
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) {
        return 0;
    }

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32*)Data;
    u32 referenceType = *(u32*)(Data + sizeof(u32));
    GF_ISOTrackID refTrackID = *(GF_ISOTrackID*)(Data + 2 * sizeof(u32));

    // Fuzz gf_isom_get_cts_to_dts_shift
    s64 cts_dts_shift = gf_isom_get_cts_to_dts_shift(isom_file, trackNumber);

    // Fuzz gf_isom_get_max_sample_delta
    u32 max_sample_delta = gf_isom_get_max_sample_delta(isom_file, trackNumber);

    // Fuzz gf_isom_get_constant_sample_size
    u32 constant_sample_size = gf_isom_get_constant_sample_size(isom_file, trackNumber);

    // Fuzz gf_isom_get_media_type
    u32 media_type = gf_isom_get_media_type(isom_file, trackNumber);

    // Fuzz gf_isom_has_track_reference
    u32 has_track_reference = gf_isom_has_track_reference(isom_file, trackNumber, referenceType, refTrackID);

    // Fuzz gf_isom_get_max_sample_cts_offset
    u32 max_sample_cts_offset = gf_isom_get_max_sample_cts_offset(isom_file, trackNumber);

    // Cleanup
    gf_isom_close(isom_file);
    return 0;
}