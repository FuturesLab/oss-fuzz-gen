// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_subtitle_set_mime at sample_descs.c:1294:8 in isomedia.h
// gf_isom_get_data_reference at isom_read.c:1723:8 in isomedia.h
// gf_isom_new_stxt_description at sample_descs.c:1418:8 in isomedia.h
// gf_isom_3gp_config_new at sample_descs.c:567:8 in isomedia.h
// gf_isom_new_text_description at tx3g.c:197:8 in isomedia.h
// gf_isom_ac4_config_new at sample_descs.c:775:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define GF_FOURCC(a, b, c, d) ((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))

static GF_ISOFile* create_dummy_iso_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite("dummy", 1, 5, file);
        fclose(file);
    }
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_248(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isoFile = create_dummy_iso_file();
    if (!isoFile) return 0;

    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    char *mime = NULL;
    u32 outDescriptionIndex = 0;
    GF_3GPConfig *config = NULL;
    GF_AC4Config *ac4Config = NULL;
    GF_TextSampleDescriptor *textDesc = NULL;

    if (Size > 0) {
        mime = (char *)malloc(Size + 1);
        if (mime) {
            memcpy(mime, Data, Size);
            mime[Size] = '\0';
        }
    }

    // Test gf_isom_subtitle_set_mime
    gf_isom_subtitle_set_mime(isoFile, trackNumber, sampleDescriptionIndex, mime);

    // Test gf_isom_get_data_reference
    const char *outURL = NULL;
    const char *outURN = NULL;
    gf_isom_get_data_reference(isoFile, trackNumber, sampleDescriptionIndex, &outURL, &outURN);

    // Test gf_isom_new_stxt_description
    gf_isom_new_stxt_description(isoFile, trackNumber, GF_FOURCC('s','b','t','t'), mime, NULL, NULL, &outDescriptionIndex);

    // Test gf_isom_3gp_config_new
    gf_isom_3gp_config_new(isoFile, trackNumber, config, NULL, NULL, &outDescriptionIndex);

    // Test gf_isom_new_text_description
    gf_isom_new_text_description(isoFile, trackNumber, textDesc, NULL, NULL, &outDescriptionIndex);

    // Test gf_isom_ac4_config_new
    gf_isom_ac4_config_new(isoFile, trackNumber, ac4Config, NULL, NULL, &outDescriptionIndex);

    // Cleanup
    if (mime) {
        free(mime);
    }
    cleanup_iso_file(isoFile);

    return 0;
}