#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Return a NULL pointer for GF_ISOFile as we cannot allocate it directly
    return NULL;
}

static GF_AC3Config* create_dummy_ac3_config() {
    // Create a dummy AC3 config
    GF_AC3Config *config = (GF_AC3Config*)malloc(sizeof(GF_AC3Config));
    if (config) {
        memset(config, 0, sizeof(GF_AC3Config));
    }
    return config;
}

int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for track number

    GF_ISOFile *iso_file = create_dummy_iso_file();
    GF_ISOFile *orig_file = create_dummy_iso_file();
    GF_AC3Config *ac3_config = create_dummy_ac3_config();

    u32 trackNumber = *(u32*)Data;
    const char *nameUTF8 = (const char*)(Data + 4);
    const char *URLname = (Size > 8) ? (const char*)(Data + 8) : NULL;
    const char *URNname = (Size > 12) ? (const char*)(Data + 12) : NULL;

    u32 outDescriptionIndex;
    char *scheme = NULL;
    char *value = NULL;

    // Fuzz gf_isom_set_handler_name
    gf_isom_set_handler_name(iso_file, trackNumber, nameUTF8);

    // Fuzz gf_isom_ac3_config_new
    gf_isom_ac3_config_new(iso_file, trackNumber, ac3_config, URLname, URNname, &outDescriptionIndex);

    // Fuzz gf_isom_clone_sample_description
    gf_isom_clone_sample_description(iso_file, trackNumber, orig_file, trackNumber, outDescriptionIndex, URLname, URNname, &outDescriptionIndex);

    // Fuzz gf_isom_get_track_kind
    gf_isom_get_track_kind(iso_file, trackNumber, 1, &scheme, &value);

    // Fuzz gf_isom_sdp_add_track_line
    gf_isom_sdp_add_track_line(iso_file, trackNumber, nameUTF8);

    // Fuzz gf_isom_get_handler_name
    const char *outName = NULL;
    gf_isom_get_handler_name(iso_file, trackNumber, &outName);

    // Clean up
    if (scheme) free(scheme);
    if (value) free(value);
    free(ac3_config);

    return 0;
}