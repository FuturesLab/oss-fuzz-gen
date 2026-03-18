// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_add_subsample at isom_write.c:7028:8 in isomedia.h
// gf_isom_fragment_add_sample at movie_fragments.c:2998:8 in isomedia.h
// gf_isom_get_track_count at isom_read.c:783:5 in isomedia.h
// gf_isom_get_sample_count at isom_read.c:1767:5 in isomedia.h
// gf_isom_sample_get_subsample at isom_read.c:4919:8 in isomedia.h
// gf_isom_setup_track_fragment at movie_fragments.c:262:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_add_sample_aux_info at isom_write.c:9301:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE "./dummy_file"

static GF_ISOFile* initialize_iso_file() {
    GF_ISOFile *file = gf_isom_open(DUMMY_FILE, GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < (4 * sizeof(u32) + sizeof(u8) + sizeof(u32) + sizeof(Bool))) return 0;

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)(Data + sizeof(u32));
    u32 flags = *(u32 *)(Data + 2 * sizeof(u32));
    u32 subSampleSize = *(u32 *)(Data + 3 * sizeof(u32));
    u8 priority = *(u8 *)(Data + 4 * sizeof(u32));
    u32 reserved = *(u32 *)(Data + 4 * sizeof(u32) + sizeof(u8));
    Bool discardable = *(Bool *)(Data + 4 * sizeof(u32) + sizeof(u8) + sizeof(u32));

    // Call gf_isom_add_subsample
    gf_isom_add_subsample(isom_file, trackNumber, sampleNumber, flags, subSampleSize, priority, reserved, discardable);

    // Call gf_isom_fragment_add_sample
    GF_ISOSample sample;
    memset(&sample, 0, sizeof(GF_ISOSample));
    u32 sampleDescriptionIndex = 0;
    u32 Duration = 1000;
    u8 PaddingBits = 0;
    u16 DegradationPriority = 0;
    Bool redundantCoding = 0;
    gf_isom_fragment_add_sample(isom_file, trackNumber, &sample, sampleDescriptionIndex, Duration, PaddingBits, DegradationPriority, redundantCoding);

    // Call gf_isom_sample_get_subsample with validation
    u32 subSampleNumber = 1;
    u32 size = 0;
    u8 out_priority = 0;
    u32 out_reserved = 0;
    Bool out_discardable = 0;
    if (trackNumber < gf_isom_get_track_count(isom_file) &&
        sampleNumber > 0 &&
        gf_isom_get_sample_count(isom_file, trackNumber) >= sampleNumber) {
        gf_isom_sample_get_subsample(isom_file, trackNumber, sampleNumber, flags, subSampleNumber, &size, &out_priority, &out_reserved, &out_discardable);
    }

    // Call gf_isom_setup_track_fragment
    u32 DefaultSampleDescriptionIndex = 1;
    u32 DefaultSampleDuration = 1000;
    u32 DefaultSampleSize = 0;
    u8 DefaultSampleSyncFlags = 0;
    u8 DefaultSamplePadding = 0;
    u16 DefaultDegradationPriority = 0;
    Bool force_traf_flags = 0;
    gf_isom_setup_track_fragment(isom_file, trackNumber, DefaultSampleDescriptionIndex, DefaultSampleDuration, DefaultSampleSize, DefaultSampleSyncFlags, DefaultSamplePadding, DefaultDegradationPriority, force_traf_flags);

    // Call gf_isom_cenc_get_sample_aux_info
    u32 sampleDescIndex = 0;
    u32 container_type = 0;
    u8 *out_buffer = NULL;
    u32 outSize = 0;
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);
    free(out_buffer);

    // Call gf_isom_add_sample_aux_info
    u32 aux_type = 1;
    u32 aux_info = 0;
    u8 data_to_add[10] = {0};
    gf_isom_add_sample_aux_info(isom_file, trackNumber, sampleNumber, aux_type, aux_info, data_to_add, sizeof(data_to_add));

    cleanup_iso_file(isom_file);
    return 0;
}