// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_mvc_config_get at avc_ext.c:2589:15 in isomedia.h
// gf_isom_avc_config_get at avc_ext.c:2468:15 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_avc_config_update at avc_ext.c:1765:8 in isomedia.h
// gf_isom_mvc_config_update at avc_ext.c:1777:8 in isomedia.h
// gf_isom_mvc_config_update at avc_ext.c:1777:8 in isomedia.h
// gf_isom_svc_config_update at avc_ext.c:1771:8 in isomedia.h
// gf_isom_svc_config_update at avc_ext.c:1771:8 in isomedia.h
// gf_isom_svc_config_get at avc_ext.c:2572:15 in isomedia.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2) return 0;

    // Prepare the environment
    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    Data += sizeof(u32) * 2;
    Size -= sizeof(u32) * 2;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Test gf_isom_mvc_config_get
    GF_AVCConfig *mvcConfig = gf_isom_mvc_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (mvcConfig) {
        gf_free(mvcConfig);
    }

    // Test gf_isom_avc_config_get
    GF_AVCConfig *avcConfig = gf_isom_avc_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (avcConfig) {
        gf_free(avcConfig);
    }

    // Prepare a dummy AVCConfig for update functions
    GF_AVCConfig *dummyConfig = (GF_AVCConfig *)malloc(sizeof(GF_AVCConfig));
    if (!dummyConfig) {
        gf_isom_close(isom_file);
        return 0;
    }

    // Test gf_isom_avc_config_update
    gf_isom_avc_config_update(isom_file, trackNumber, sampleDescriptionIndex, dummyConfig);

    // Test gf_isom_mvc_config_update with is_additional set to 0 and 1
    gf_isom_mvc_config_update(isom_file, trackNumber, sampleDescriptionIndex, dummyConfig, 0);
    gf_isom_mvc_config_update(isom_file, trackNumber, sampleDescriptionIndex, dummyConfig, 1);

    // Test gf_isom_svc_config_update with is_additional set to 0 and 1
    gf_isom_svc_config_update(isom_file, trackNumber, sampleDescriptionIndex, dummyConfig, 0);
    gf_isom_svc_config_update(isom_file, trackNumber, sampleDescriptionIndex, dummyConfig, 1);

    // Test gf_isom_svc_config_get
    GF_AVCConfig *svcConfig = gf_isom_svc_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (svcConfig) {
        gf_free(svcConfig);
    }

    // Cleanup
    free(dummyConfig);
    gf_isom_close(isom_file);

    return 0;
}