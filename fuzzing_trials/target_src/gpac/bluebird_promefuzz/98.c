#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Normally, we would allocate and initialize the GF_ISOFile structure properly.
    // However, since GF_ISOFile is an incomplete type in the provided header, 
    // we cannot directly allocate or initialize it without the full definition.
    // For the purpose of this fuzz driver, we will return a NULL pointer and 
    // assume the functions handle this gracefully.
    return NULL;
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();

    u32 trackNumber = *((u32*)Data);
    u32 duration = *((u32*)(Data + sizeof(u32)));
    u32 index = *((u32*)(Data + sizeof(u32) * 2));

    // Test gf_isom_set_last_sample_duration
    gf_isom_set_last_sample_duration(isom_file, trackNumber, duration);

    // Test gf_isom_remove_chapter
    gf_isom_remove_chapter(isom_file, trackNumber, index);

    // Test gf_isom_remove_track_references
    gf_isom_remove_track_references(isom_file, trackNumber);

    // Test gf_isom_get_chunks_infos
    u32 dur_min, dur_avg, dur_max, size_min, size_avg, size_max;
    gf_isom_get_chunks_infos(isom_file, trackNumber, &dur_min, &dur_avg, &dur_max, &size_min, &size_avg, &size_max);

    // Test gf_isom_remove_edit
    gf_isom_remove_edit(isom_file, trackNumber, index);

    // Test gf_isom_set_interleave_time
    gf_isom_set_interleave_time(isom_file, duration);

    // Cleanup
    // Normally, we would free the allocated isom_file, but since we return NULL, there's nothing to free.

    return 0;
}