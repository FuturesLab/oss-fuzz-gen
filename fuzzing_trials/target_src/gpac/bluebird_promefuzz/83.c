#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2 + 1) {
        return 0; // Not enough data
    }

    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!iso_file) {
        return 0; // Failed to open or create dummy ISO file
    }

    u32 trackNumber = *((u32*)Data);
    u32 sampleDescriptionIndex = *((u32*)(Data + sizeof(u32)));
    Bool is_additional = (Bool)(Data[sizeof(u32) * 2] % 2);

    GF_AVCConfig* avc_config = gf_isom_avc_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (avc_config) {
        free(avc_config);
    }

    GF_AVCConfig* svc_config = gf_isom_svc_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (svc_config) {
        free(svc_config);
    }

    GF_AVCConfig* mvc_config = gf_isom_mvc_config_get(iso_file, trackNumber, sampleDescriptionIndex);
    if (mvc_config) {
        free(mvc_config);
    }

    GF_Err err_mvc_update = gf_isom_mvc_config_update(iso_file, trackNumber, sampleDescriptionIndex, avc_config, is_additional);

    GF_Err err_svc_update = gf_isom_svc_config_update(iso_file, trackNumber, sampleDescriptionIndex, avc_config, is_additional);

    GF_Err err_avc_update = gf_isom_avc_config_update(iso_file, trackNumber, sampleDescriptionIndex, avc_config);

    (void)err_mvc_update; // Suppress unused variable warnings
    (void)err_svc_update;
    (void)err_avc_update;

    gf_isom_close(iso_file);

    return 0;
}