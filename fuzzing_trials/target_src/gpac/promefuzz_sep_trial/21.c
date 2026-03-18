// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_update_sample_reference at isom_write.c:1477:8 in isomedia.h
// gf_isom_get_sample_info at isom_read.c:2133:15 in isomedia.h
// gf_isom_get_sample_info_ex at isom_read.c:2099:15 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_get_sample at isom_read.c:1984:15 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_get_sample_ex at isom_read.c:1937:15 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void initialize_sample(GF_ISOSample *sample) {
    if (sample) {
        sample->data = NULL;
        sample->dataLength = 1; // Ensure non-NULL data length
    }
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (!sample) {
        gf_isom_close(isom_file);
        return 0;
    }
    initialize_sample(sample);

    u32 trackNumber = 1;
    u32 sampleNumber = 1;
    u32 sampleDescriptionIndex = 0;
    u64 dataOffset = 0;

    // Create a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        free(sample);
        gf_isom_close(isom_file);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Fuzz gf_isom_update_sample_reference
    gf_isom_update_sample_reference(isom_file, trackNumber, sampleNumber, sample, dataOffset);

    // Fuzz gf_isom_get_sample_info
    gf_isom_get_sample_info(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &dataOffset);

    // Fuzz gf_isom_get_sample_info_ex
    gf_isom_get_sample_info_ex(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, &dataOffset, sample);

    // Fuzz gf_isom_add_sample_reference
    gf_isom_add_sample_reference(isom_file, trackNumber, sampleDescriptionIndex, sample, dataOffset);

    // Fuzz gf_isom_get_sample
    GF_ISOSample *retrieved_sample = gf_isom_get_sample(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex);
    if (retrieved_sample) {
        gf_isom_sample_del(&retrieved_sample);
    }

    // Fuzz gf_isom_get_sample_ex
    gf_isom_get_sample_ex(isom_file, trackNumber, sampleNumber, &sampleDescriptionIndex, sample, &dataOffset);

    // Cleanup
    free(sample);
    gf_isom_close(isom_file);

    return 0;
}