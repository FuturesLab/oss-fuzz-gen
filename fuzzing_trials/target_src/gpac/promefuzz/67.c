// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_3gp_config_update at sample_descs.c:660:8 in isomedia.h
// gf_isom_3gp_config_get at sample_descs.c:304:15 in isomedia.h
// gf_isom_is_track_referenced at isom_read.c:1316:5 in isomedia.h
// gf_isom_get_track_switch_parameter at isom_read.c:4831:12 in isomedia.h
// gf_isom_get_track_original_id at isom_read.c:824:15 in isomedia.h
// gf_isom_get_track_flags at isom_read.c:1064:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Creating a dummy file for the purpose of fuzzing
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fclose(file);

    // Open the file using gpac's API
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 referenceType = *(u32 *)(Data + sizeof(u32) * 2);

    GF_3GPConfig config;
    memset(&config, 0, sizeof(GF_3GPConfig)); // Initialize config with zeros

    // Fuzz gf_isom_3gp_config_update
    gf_isom_3gp_config_update(iso_file, trackNumber, &config, sampleDescriptionIndex);

    // Fuzz gf_isom_3gp_config_get
    GF_3GPConfig *retrieved_config = gf_isom_3gp_config_get(iso_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_is_track_referenced
    u32 referencing_track = gf_isom_is_track_referenced(iso_file, trackNumber, referenceType);

    // Fuzz gf_isom_get_track_switch_parameter
    u32 switchGroupID = 0;
    u32 criteriaListSize = 0;
    const u32 *criteriaList = gf_isom_get_track_switch_parameter(iso_file, trackNumber, sampleDescriptionIndex, &switchGroupID, &criteriaListSize);

    // Fuzz gf_isom_get_track_original_id
    GF_ISOTrackID original_id = gf_isom_get_track_original_id(iso_file, trackNumber);

    // Fuzz gf_isom_get_track_flags
    u32 track_flags = gf_isom_get_track_flags(iso_file, trackNumber);

    cleanup_iso_file(iso_file);

    return 0;
}