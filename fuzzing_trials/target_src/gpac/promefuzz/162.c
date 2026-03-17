// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_remove_stream_description at isom_write.c:909:8 in isomedia.h
// gf_isom_hevc_config_update at avc_ext.c:2318:8 in isomedia.h
// gf_isom_evte_config_new at sample_descs.c:1846:8 in isomedia.h
// gf_isom_set_visual_info at isom_write.c:1769:8 in isomedia.h
// gf_isom_lhvc_config_update at avc_ext.c:2343:8 in isomedia.h
// gf_isom_set_forced_text at tx3g.c:973:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Create a dummy file on disk to simulate the ISO file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) return NULL;
    fclose(dummy_file);

    // Open the dummy file as an ISO file
    GF_ISOFile *isofile = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isofile;
}

static GF_HEVCConfig* create_dummy_hevc_config() {
    GF_HEVCConfig *config = malloc(sizeof(GF_HEVCConfig));
    if (!config) return NULL;
    memset(config, 0, sizeof(GF_HEVCConfig));
    return config;
}

int LLVMFuzzerTestOneInput_162(const uint8_t *Data, size_t Size) {
    if (Size < 12) return 0;

    GF_ISOFile *isofile = create_dummy_isofile();
    if (!isofile) return 0;

    GF_HEVCConfig *hevc_config = create_dummy_hevc_config();
    if (!hevc_config) {
        gf_isom_close(isofile);
        return 0;
    }

    u32 trackNumber = (u32)Data[0];
    u32 sampleDescriptionIndex = (u32)Data[1];
    u32 Width = (u32)Data[2];
    u32 Height = (u32)Data[3];
    u32 force_type = (u32)Data[4];
    GF_ISOMLHEVCTrackType track_type = (GF_ISOMLHEVCTrackType)Data[5];

    gf_isom_remove_stream_description(isofile, trackNumber, sampleDescriptionIndex);
    gf_isom_hevc_config_update(isofile, trackNumber, sampleDescriptionIndex, hevc_config);
    gf_isom_evte_config_new(isofile, trackNumber, &sampleDescriptionIndex);
    gf_isom_set_visual_info(isofile, trackNumber, sampleDescriptionIndex, Width, Height);
    gf_isom_lhvc_config_update(isofile, trackNumber, sampleDescriptionIndex, hevc_config, track_type);
    gf_isom_set_forced_text(isofile, trackNumber, sampleDescriptionIndex, force_type);

    free(hevc_config);
    gf_isom_close(isofile);

    return 0;
}