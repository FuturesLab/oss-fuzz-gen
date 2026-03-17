#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // Assuming there's a function in the actual library to create an ISOFile.
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static GF_HEVCConfig* create_dummy_hevc_config() {
    GF_HEVCConfig *config = malloc(sizeof(GF_HEVCConfig));
    if (!config) return NULL;
    memset(config, 0, sizeof(GF_HEVCConfig));
    return config;
}

int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(Bool)) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    GF_HEVCConfig *hevc_config = create_dummy_hevc_config();
    if (!hevc_config) {
        gf_isom_close(iso_file);
        return 0;
    }

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 outDescriptionIndex = 0;
    Bool is_base_track = *((Bool *)(Data + sizeof(u32) * 2));

    gf_isom_lhvc_config_update(iso_file, trackNumber, sampleDescriptionIndex, hevc_config, 0);
    gf_isom_hevc_set_tile_config(iso_file, trackNumber, sampleDescriptionIndex, hevc_config, is_base_track);
    GF_HEVCConfig *retrieved_config = gf_isom_hevc_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (retrieved_config) free(retrieved_config);
    retrieved_config = gf_isom_lhvc_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (retrieved_config) free(retrieved_config);
    gf_isom_hevc_config_new(iso_file, trackNumber, hevc_config, NULL, NULL, &outDescriptionIndex);
    gf_isom_hevc_config_update(iso_file, trackNumber, sampleDescriptionIndex, hevc_config);

    free(hevc_config);
    gf_isom_close(iso_file);
    return 0;
}