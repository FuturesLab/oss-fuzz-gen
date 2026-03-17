// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_sample_info at isom_read.c:2133:15 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_sample_new at isom_read.c:100:15 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_get_sample_ex at isom_read.c:1937:15 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assuming GF_ISOFile creation is handled by a specific function in the library
    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile* iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_315(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u32 sampleNumber = *((u32*)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = *((u32*)(Data + sizeof(u32) * 2));
    u64 dataOffset = 0;
    
    GF_ISOSample* sample = gf_isom_get_sample_info(iso_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &dataOffset);
    if (sample) {
        gf_isom_sample_del(&sample);
    }

    GF_ISOSample* new_sample = gf_isom_sample_new();
    if (new_sample) {
        gf_isom_add_sample_reference(iso_file, trackNumber, sampleDescriptionIndex, new_sample, dataOffset);
        gf_isom_sample_del(&new_sample);
    }

    GF_ISOSample* static_sample = (GF_ISOSample*)malloc(sizeof(GF_ISOSample));
    if (static_sample) {
        memset(static_sample, 0, sizeof(GF_ISOSample));
        gf_isom_get_sample_ex(iso_file, trackNumber, sampleNumber, &sampleDescriptionIndex, static_sample, &dataOffset);
        free(static_sample);
    }

    cleanup_iso_file(iso_file);
    return 0;
}