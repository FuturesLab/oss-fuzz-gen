// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_add_subsample at isom_write.c:7028:8 in isomedia.h
// gf_isom_fragment_add_subsample at movie_fragments.c:3133:8 in isomedia.h
// gf_isom_get_track_by_id at isom_read.c:807:5 in isomedia.h
// gf_isom_sample_get_subsample at isom_read.c:4919:8 in isomedia.h
// gf_isom_fragment_add_sample at movie_fragments.c:2998:8 in isomedia.h
// gf_isom_fragment_set_cenc_sai at movie_fragments.c:3005:8 in isomedia.h
// gf_isom_set_sample_rap_group at isom_write.c:7715:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 6 + sizeof(u8) + sizeof(Bool)) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)(Data);
    u32 sampleNumber = *(u32 *)(Data + sizeof(u32));
    u32 flags = *(u32 *)(Data + sizeof(u32) * 2);
    u32 subSampleSize = *(u32 *)(Data + sizeof(u32) * 3);
    u8 priority = *(u8 *)(Data + sizeof(u32) * 4);
    u32 reserved = *(u32 *)(Data + sizeof(u32) * 4 + sizeof(u8));
    Bool discardable = *(Bool *)(Data + sizeof(u32) * 5 + sizeof(u8));

    GF_Err err;

    // Fuzz gf_isom_add_subsample
    err = gf_isom_add_subsample(isom_file, trackNumber, sampleNumber, flags, subSampleSize, priority, reserved, discardable);
    if (err) {
        // Handle error
    }

    // Fuzz gf_isom_fragment_add_subsample
    err = gf_isom_fragment_add_subsample(isom_file, trackNumber, flags, subSampleSize, priority, reserved, discardable);
    if (err) {
        // Handle error
    }

    // Initialize output variables for gf_isom_sample_get_subsample
    u32 size_out = 0;
    u8 priority_out = 0;
    u32 reserved_out = 0;
    Bool discardable_out = GF_FALSE;

    // Check if the track and sample are valid before calling gf_isom_sample_get_subsample
    if (gf_isom_get_track_by_id(isom_file, trackNumber) != NULL) {
        err = gf_isom_sample_get_subsample(isom_file, trackNumber, sampleNumber, flags, 1, &size_out, &priority_out, &reserved_out, &discardable_out);
        if (err) {
            // Handle error
        }
    }

    // Fuzz gf_isom_fragment_add_sample
    GF_ISOSample sample;
    memset(&sample, 0, sizeof(GF_ISOSample));
    err = gf_isom_fragment_add_sample(isom_file, trackNumber, &sample, 0, 0, 0, 0, 0);
    if (err) {
        // Handle error
    }

    // Fuzz gf_isom_fragment_set_cenc_sai
    u8 sai_b[16] = {0};
    err = gf_isom_fragment_set_cenc_sai(isom_file, trackNumber, sai_b, sizeof(sai_b), 0, 0, 0);
    if (err) {
        // Handle error
    }

    // Fuzz gf_isom_set_sample_rap_group
    err = gf_isom_set_sample_rap_group(isom_file, trackNumber, sampleNumber, 0, 0);
    if (err) {
        // Handle error
    }

    gf_isom_close(isom_file);
    return 0;
}