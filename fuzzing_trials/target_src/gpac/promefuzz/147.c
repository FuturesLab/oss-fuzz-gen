// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_info at isom_read.c:2133:15 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_get_sample_info_ex at isom_read.c:2099:15 in isomedia.h
// gf_isom_get_sample at isom_read.c:1984:15 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_update_sample_reference at isom_write.c:1477:8 in isomedia.h
// gf_isom_get_sample_ex at isom_read.c:1937:15 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(u32) + sizeof(u64)) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)(Data));
    u32 sampleNumber = *((u32 *)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = 0;
    u64 dataOffset = 0;

    GF_ISOSample static_sample;
    memset(&static_sample, 0, sizeof(GF_ISOSample));

    // Write dummy file
    write_dummy_file(Data, Size);

    // Fuzz gf_isom_get_sample_info
    GF_ISOSample *sample_info = gf_isom_get_sample_info(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &dataOffset);
    if (sample_info) {
        // Handle sample info
    }

    // Fuzz gf_isom_add_sample_reference
    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (sample) {
        gf_isom_add_sample_reference(isom_file, trackNumber, sampleDescriptionIndex, sample, dataOffset);
        free(sample);
    }

    // Fuzz gf_isom_get_sample_info_ex
    GF_ISOSample *sample_info_ex = gf_isom_get_sample_info_ex(isom_file, trackNumber, sampleNumber, NULL, NULL, &static_sample);
    if (sample_info_ex) {
        // Handle sample info ex
    }

    // Fuzz gf_isom_get_sample
    GF_ISOSample *sample_get = gf_isom_get_sample(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex);
    if (sample_get) {
        // Handle sample get
        gf_isom_sample_del(sample_get);
    }

    // Fuzz gf_isom_update_sample_reference
    GF_ISOSample *new_sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (new_sample) {
        gf_isom_update_sample_reference(isom_file, trackNumber, sampleNumber, new_sample, dataOffset);
        free(new_sample);
    }

    // Fuzz gf_isom_get_sample_ex
    GF_ISOSample *sample_ex = gf_isom_get_sample_ex(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &static_sample, &dataOffset);
    if (sample_ex) {
        // Handle sample ex
    }

    // Clean up
    gf_isom_close(isom_file);
    return 0;
}