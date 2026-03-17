// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_for_movie_time at isom_read.c:2365:8 in isomedia.h
// gf_isom_get_sample_for_media_time at isom_read.c:2192:8 in isomedia.h
// gf_isom_update_sample_reference at isom_write.c:1477:8 in isomedia.h
// gf_isom_add_sample at isom_write.c:1061:8 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_get_media_time at isom_read.c:1342:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void prepare_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        // Write some dummy content to the file
        const char *dummy_content = "dummy content";
        fwrite(dummy_content, 1, sizeof(dummy_content), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + sizeof(u64)) return 0;

    prepare_dummy_file();

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u64 movieTime = *((u64 *)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = 0;
    GF_ISOSample *sample = NULL;
    u32 sample_number = 0;
    u64 data_offset = 0;

    // Using a valid search mode, assuming GF_ISOM_SEARCH_FORWARD is valid
    gf_isom_get_sample_for_movie_time(isom_file, trackNumber, movieTime, &sampleDescriptionIndex, GF_ISOM_SEARCH_FORWARD, &sample, &sample_number, &data_offset);

    gf_isom_get_sample_for_media_time(isom_file, trackNumber, movieTime, &sampleDescriptionIndex, GF_ISOM_SEARCH_FORWARD, &sample, &sample_number, &data_offset);

    GF_ISOSample new_sample = {0};
    new_sample.dataLength = 1; // Ensure dataLength is non-zero
    gf_isom_update_sample_reference(isom_file, trackNumber, sample_number, &new_sample, data_offset);

    gf_isom_add_sample(isom_file, trackNumber, sampleDescriptionIndex, &new_sample);

    gf_isom_add_sample_reference(isom_file, trackNumber, sampleDescriptionIndex, &new_sample, data_offset);

    u64 mediaTime = 0;
    gf_isom_get_media_time(isom_file, trackNumber, movieTime, &mediaTime);

    gf_isom_close(isom_file);
    return 0;
}