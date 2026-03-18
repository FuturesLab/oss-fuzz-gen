// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_ac3_config_update at sample_descs.c:746:8 in isomedia.h
// gf_isom_set_sample_flags at isom_write.c:8052:8 in isomedia.h
// gf_isom_ac3_config_new at sample_descs.c:701:8 in isomedia.h
// gf_isom_set_track_interleaving_group at isom_write.c:5868:8 in isomedia.h
// gf_isom_get_audio_info at isom_read.c:3880:8 in isomedia.h
// gf_isom_ac3_config_get at sample_descs.c:342:15 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile *initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Assuming GF_ISOFile is initialized via a specific function
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!iso_file) return NULL;

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        gf_isom_close(iso_file);
        return NULL;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
        remove("./dummy_file");
    }
}

int LLVMFuzzerTestOneInput_252(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)(Data);
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 sampleNumber = *(u32 *)(Data + 2 * sizeof(u32));

    GF_AC3Config ac3Config;
    memset(&ac3Config, 0, sizeof(GF_AC3Config));

    u32 SampleRate, Channels, bitsPerSample;
    u32 isLeading = 0, dependsOn = 0, dependedOn = 0, redundant = 0;
    u32 outDescriptionIndex;
    const char *URLname = NULL;
    const char *URNname = NULL;
    u32 GroupID = 1;

    gf_isom_ac3_config_update(isom_file, trackNumber, sampleDescriptionIndex, &ac3Config);
    gf_isom_set_sample_flags(isom_file, trackNumber, sampleNumber, isLeading, dependsOn, dependedOn, redundant);
    gf_isom_ac3_config_new(isom_file, trackNumber, &ac3Config, URLname, URNname, &outDescriptionIndex);
    gf_isom_set_track_interleaving_group(isom_file, trackNumber, GroupID);
    gf_isom_get_audio_info(isom_file, trackNumber, sampleDescriptionIndex, &SampleRate, &Channels, &bitsPerSample);
    GF_AC3Config *retrievedConfig = gf_isom_ac3_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (retrievedConfig) {
        free(retrievedConfig);
    }

    cleanup_iso_file(isom_file);
    return 0;
}