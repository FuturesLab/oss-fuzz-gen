// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_lhvc_config_get at avc_ext.c:2771:16 in isomedia.h
// gf_isom_hevc_config_get at avc_ext.c:2485:16 in isomedia.h
// gf_isom_hevc_config_update at avc_ext.c:2318:8 in isomedia.h
// gf_isom_lhvc_config_update at avc_ext.c:2343:8 in isomedia.h
// gf_isom_hevc_set_tile_config at avc_ext.c:2337:8 in isomedia.h
// gf_isom_hevc_config_new at avc_ext.c:1889:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_207(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32*)Data;
    u32 sampleDescriptionIndex = *(u32*)(Data + sizeof(u32));
    u32 track_type = *(u32*)(Data + sizeof(u32) * 2);

    // Test gf_isom_lhvc_config_get
    GF_HEVCConfig *lhvc_config = gf_isom_lhvc_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (lhvc_config) {
        free(lhvc_config);
    }

    // Test gf_isom_hevc_config_get
    GF_HEVCConfig *hevc_config = gf_isom_hevc_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (hevc_config) {
        free(hevc_config);
    }

    // Test gf_isom_hevc_config_update
    if (hevc_config) {
        gf_isom_hevc_config_update(isom_file, trackNumber, sampleDescriptionIndex, hevc_config);
    }

    // Test gf_isom_lhvc_config_update
    if (lhvc_config) {
        gf_isom_lhvc_config_update(isom_file, trackNumber, sampleDescriptionIndex, lhvc_config, track_type);
    }

    // Test gf_isom_hevc_set_tile_config
    Bool is_base_track = (Bool)(Data[Size - 1] % 2);
    gf_isom_hevc_set_tile_config(isom_file, trackNumber, sampleDescriptionIndex, hevc_config, is_base_track);

    // Test gf_isom_hevc_config_new
    u32 outDescriptionIndex;
    gf_isom_hevc_config_new(isom_file, trackNumber, hevc_config, NULL, NULL, &outDescriptionIndex);

    cleanup_iso_file(isom_file);
    return 0;
}