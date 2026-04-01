// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_track_id at isom_read.c:796:15 in isomedia.h
// gf_isom_enum_track_references at isom_read.c:1219:22 in isomedia.h
// gf_isom_av1_config_get at avc_ext.c:2605:15 in isomedia.h
// gf_isom_has_track_reference at isom_read.c:1295:5 in isomedia.h
// gf_isom_get_avg_sample_delta at isom_read.c:2052:5 in isomedia.h
// gf_isom_get_track_switch_parameter at isom_read.c:4831:12 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    // Create a dummy ISO file structure
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_302(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 idx = *((u32 *)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32) * 2));

    // Test gf_isom_get_track_id
    GF_ISOTrackID trackID = gf_isom_get_track_id(iso_file, trackNumber);

    // Test gf_isom_enum_track_references
    u32 referenceType, referenceCount;
    const GF_ISOTrackID *trackIDs = gf_isom_enum_track_references(iso_file, trackNumber, idx, &referenceType, &referenceCount);

    // Test gf_isom_av1_config_get
    GF_AV1Config *av1Config = gf_isom_av1_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (av1Config) {
        free(av1Config);  // Remember to free the allocated config
    }

    // Test gf_isom_has_track_reference
    u32 refIndex = gf_isom_has_track_reference(iso_file, trackNumber, referenceType, trackID);

    // Test gf_isom_get_avg_sample_delta
    u32 avgSampleDelta = gf_isom_get_avg_sample_delta(iso_file, trackNumber);

    // Test gf_isom_get_track_switch_parameter
    u32 switchGroupID, criteriaListSize;
    const u32 *criteriaList = gf_isom_get_track_switch_parameter(iso_file, trackNumber, idx, &switchGroupID, &criteriaListSize);

    cleanup_iso_file(iso_file);

    return 0;
}