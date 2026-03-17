// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_track_creation_time at isom_write.c:230:8 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_get_sample_for_movie_time at isom_read.c:2365:8 in isomedia.h
// gf_isom_get_media_time at isom_read.c:1342:8 in isomedia.h
// gf_isom_update_sample_reference at isom_write.c:1477:8 in isomedia.h
// gf_isom_get_sample_for_media_time at isom_read.c:2192:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // Assume the library provides a function to create or open an ISO file.
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static GF_ISOSample* initialize_iso_sample() {
    GF_ISOSample *sample = (GF_ISOSample*)malloc(sizeof(GF_ISOSample));
    if (!sample) return NULL;
    // Initialize sample with dummy data or zeroed memory
    memset(sample, 0, sizeof(GF_ISOSample));
    return sample;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

static void cleanup_iso_sample(GF_ISOSample *sample) {
    if (sample) {
        free(sample);
    }
}

int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2 + sizeof(u64) * 2) return 0;

    GF_ISOFile *iso_file = initialize_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *(u32*)(Data);
    u64 create_time = *(u64*)(Data + sizeof(u32));
    u64 modif_time = *(u64*)(Data + sizeof(u32) + sizeof(u64));

    gf_isom_set_track_creation_time(iso_file, trackNumber, create_time, modif_time);

    if (Size < sizeof(u32) * 3 + sizeof(u64) * 3) {
        cleanup_iso_file(iso_file);
        return 0;
    }

    GF_ISOSample *sample = initialize_iso_sample();
    if (!sample) {
        cleanup_iso_file(iso_file);
        return 0;
    }

    u32 sampleDescriptionIndex = *(u32*)(Data + sizeof(u32) + sizeof(u64) * 2);
    u64 dataOffset = *(u64*)(Data + sizeof(u32) * 2 + sizeof(u64) * 2);

    gf_isom_add_sample_reference(iso_file, trackNumber, sampleDescriptionIndex, sample, dataOffset);

    if (Size < sizeof(u32) * 4 + sizeof(u64) * 4) {
        cleanup_iso_sample(sample);
        cleanup_iso_file(iso_file);
        return 0;
    }

    u64 movieTime = *(u64*)(Data + sizeof(u32) * 3 + sizeof(u64) * 3);
    u32 *sampleDescriptionIndexPtr = NULL;
    GF_ISOSearchMode searchMode = *(GF_ISOSearchMode*)(Data + sizeof(u32) * 3 + sizeof(u64) * 4);
    GF_ISOSample *retrievedSample = NULL;
    u32 *sample_number = NULL;
    u64 *data_offset = NULL;

    gf_isom_get_sample_for_movie_time(iso_file, trackNumber, movieTime, sampleDescriptionIndexPtr, searchMode, &retrievedSample, sample_number, data_offset);

    u32 movieTime32 = *(u32*)(Data + sizeof(u32) * 3 + sizeof(u64) * 3);
    u64 mediaTime = 0;

    gf_isom_get_media_time(iso_file, trackNumber, movieTime32, &mediaTime);

    u32 sampleNumber = *(u32*)(Data + sizeof(u32) * 4 + sizeof(u64) * 4);

    gf_isom_update_sample_reference(iso_file, trackNumber, sampleNumber, sample, dataOffset);

    u64 desiredTime = *(u64*)(Data + sizeof(u32) * 4 + sizeof(u64) * 4);

    gf_isom_get_sample_for_media_time(iso_file, trackNumber, desiredTime, sampleDescriptionIndexPtr, searchMode, &retrievedSample, sample_number, data_offset);

    cleanup_iso_sample(sample);
    cleanup_iso_file(iso_file);
    
    return 0;
}