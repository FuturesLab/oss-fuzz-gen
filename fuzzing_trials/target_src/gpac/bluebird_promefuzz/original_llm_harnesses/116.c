// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_lpcm_config at sample_descs.c:2015:8 in isomedia.h
// gf_isom_get_track_switch_group_count at isom_read.c:4813:8 in isomedia.h
// gf_isom_opus_config_get at sample_descs.c:551:8 in isomedia.h
// gf_isom_get_alternate_brand at isom_read.c:2648:8 in isomedia.h
// gf_isom_get_pcm_config at sample_descs.c:1972:8 in isomedia.h
// gf_isom_get_brand_info at isom_read.c:2631:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u32 sampleDescriptionIndex = *((u32*)(Data + sizeof(u32)));
    u32 BrandIndex = *((u32*)(Data + 2 * sizeof(u32)));
    u32 *brand = (u32*)(Data + 3 * sizeof(u32));

    Double sample_rate;
    u32 nb_channels, flags, pcm_size;
    u8 *dsi = NULL;
    u32 dsi_size;

    gf_isom_get_lpcm_config(isom_file, trackNumber, sampleDescriptionIndex, &sample_rate, &nb_channels, &flags, &pcm_size);
    gf_isom_get_track_switch_group_count(isom_file, trackNumber, &nb_channels, &flags);
    gf_isom_opus_config_get(isom_file, trackNumber, sampleDescriptionIndex, &dsi, &dsi_size);
    if (dsi) free(dsi);
    gf_isom_get_alternate_brand(isom_file, BrandIndex, brand);
    gf_isom_get_pcm_config(isom_file, trackNumber, sampleDescriptionIndex, &flags, &pcm_size);
    gf_isom_get_brand_info(isom_file, brand, &nb_channels, &flags);

    gf_isom_close(isom_file);

    return 0;
}