// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_track_id at isom_read.c:796:15 in isomedia.h
// gf_isom_enum_track_references at isom_read.c:1219:22 in isomedia.h
// gf_isom_av1_config_get at avc_ext.c:2605:15 in isomedia.h
// gf_isom_get_avg_sample_delta at isom_read.c:2052:5 in isomedia.h
// gf_isom_has_track_reference at isom_read.c:1295:5 in isomedia.h
// gf_isom_get_track_switch_parameter at isom_read.c:4831:12 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

// Helper function to create a dummy GF_ISOFile
static GF_ISOFile* create_dummy_iso_file() {
    // Allocate a dummy size for the GF_ISOFile
    GF_ISOFile* iso_file = (GF_ISOFile*)malloc(1024);
    if (!iso_file) return NULL;
    memset(iso_file, 0, 1024);
    return iso_file;
}

// Helper function to clean up the dummy GF_ISOFile
static void cleanup_dummy_iso_file(GF_ISOFile* iso_file) {
    if (iso_file) {
        free(iso_file);
    }
}

int LLVMFuzzerTestOneInput_298(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Extract trackNumber from the input data
    u32 trackNumber = *(u32*)Data;

    // Fuzz gf_isom_get_track_id
    GF_ISOTrackID track_id = gf_isom_get_track_id(iso_file, trackNumber);

    // Fuzz gf_isom_enum_track_references
    u32 referenceType, referenceCount;
    const GF_ISOTrackID *references = gf_isom_enum_track_references(iso_file, trackNumber, 0, &referenceType, &referenceCount);

    // Fuzz gf_isom_av1_config_get
    GF_AV1Config *av1_config = gf_isom_av1_config_get(iso_file, trackNumber, 0);
    if (av1_config) {
        free(av1_config); // Clean up if a valid config was returned
    }

    // Fuzz gf_isom_get_avg_sample_delta
    u32 avg_sample_delta = gf_isom_get_avg_sample_delta(iso_file, trackNumber);

    // Fuzz gf_isom_has_track_reference
    u32 ref_index = gf_isom_has_track_reference(iso_file, trackNumber, referenceType, track_id);

    // Fuzz gf_isom_get_track_switch_parameter
    u32 switchGroupID, criteriaListSize;
    const u32 *criteria = gf_isom_get_track_switch_parameter(iso_file, trackNumber, 1, &switchGroupID, &criteriaListSize);

    cleanup_dummy_iso_file(iso_file);

    return 0;
}