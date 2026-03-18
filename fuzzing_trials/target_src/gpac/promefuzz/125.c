// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_info at isom_read.c:2133:15 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_sample_new at isom_read.c:100:15 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_get_sample at isom_read.c:1984:15 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_get_sample_ex at isom_read.c:1937:15 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
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
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    // Prepare dummy file
    write_dummy_file(Data, Size);

    // Initialize variables
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)(Data + sizeof(u32));
    u32 sampleDescriptionIndex = 0;
    u64 dataOffset = 0;

    // Fuzz gf_isom_get_sample_info
    GF_ISOSample *sample_info = gf_isom_get_sample_info(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &dataOffset);
    if (sample_info) {
        gf_isom_sample_del(&sample_info);
    }

    // Fuzz gf_isom_sample_new
    GF_ISOSample *new_sample = gf_isom_sample_new();
    if (new_sample) {
        // Fuzz gf_isom_add_sample_reference
        gf_isom_add_sample_reference(isom_file, trackNumber, sampleDescriptionIndex, new_sample, dataOffset);

        // Fuzz gf_isom_sample_del
        gf_isom_sample_del(&new_sample);
    }

    // Fuzz gf_isom_get_sample
    GF_ISOSample *sample = gf_isom_get_sample(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex);
    if (sample) {
        gf_isom_sample_del(&sample);
    }

    // Fuzz gf_isom_get_sample_ex
    GF_ISOSample static_sample;
    memset(&static_sample, 0, sizeof(GF_ISOSample));
    GF_ISOSample *sample_ex = gf_isom_get_sample_ex(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &static_sample, &dataOffset);
    if (sample_ex && sample_ex != &static_sample) {
        gf_isom_sample_del(&sample_ex);
    }

    // Close the ISO file
    gf_isom_close(isom_file);

    return 0;
}