// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_duration at isom_read.c:1990:5 in isomedia.h
// gf_isom_has_time_offset at isom_read.c:1868:5 in isomedia.h
// gf_isom_get_timescale at isom_read.c:962:5 in isomedia.h
// gf_isom_get_track_switch_parameter at isom_read.c:4831:12 in isomedia.h
// gf_isom_is_track_referenced at isom_read.c:1316:5 in isomedia.h
// gf_isom_segment_get_fragment_count at isom_read.c:864:5 in isomedia.h
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

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);
    
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u32 sampleNumber = Data[1];
    u32 groupIndex = Data[2];
    u32 referenceType = Data[3];

    // Test gf_isom_get_sample_duration
    u32 duration = gf_isom_get_sample_duration(isom_file, trackNumber, sampleNumber);

    // Test gf_isom_has_time_offset
    u32 has_time_offset = gf_isom_has_time_offset(isom_file, trackNumber);

    // Test gf_isom_get_timescale
    u32 timescale = gf_isom_get_timescale(isom_file);

    // Test gf_isom_get_track_switch_parameter
    u32 switchGroupID;
    u32 criteriaListSize;
    const u32 *criteriaList = gf_isom_get_track_switch_parameter(isom_file, trackNumber, groupIndex, &switchGroupID, &criteriaListSize);

    // Test gf_isom_is_track_referenced
    u32 referencedTrack = gf_isom_is_track_referenced(isom_file, trackNumber, referenceType);

    // Test gf_isom_segment_get_fragment_count
    u32 fragmentCount = gf_isom_segment_get_fragment_count(isom_file);

    gf_isom_close(isom_file);
    return 0;
}