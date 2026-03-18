// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_reset_fragment_info at isom_read.c:4976:6 in isomedia.h
// gf_isom_reset_fragment_info at isom_read.c:4976:6 in isomedia.h
// gf_isom_is_smooth_streaming_moov at isom_read.c:5848:6 in isomedia.h
// gf_isom_is_fragmented at movie_fragments.c:3523:6 in isomedia.h
// gf_isom_has_keep_utc_times at isom_read.c:5550:6 in isomedia.h
// gf_isom_has_sync_shadows at isom_read.c:1894:6 in isomedia.h
// gf_isom_has_sample_dependency at isom_read.c:1904:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    // Allocate memory for GF_ISOFile using a dummy size
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(1024); // Allocate a reasonable amount of memory
    if (!isom_file) return NULL;

    // Clear the allocated memory to simulate a zero-initialized structure
    memset(isom_file, 0, 1024);

    return isom_file;
}

int LLVMFuzzerTestOneInput_181(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    // Fuzz gf_isom_reset_fragment_info
    gf_isom_reset_fragment_info(isom_file, GF_TRUE);
    gf_isom_reset_fragment_info(isom_file, GF_FALSE);

    // Fuzz gf_isom_is_smooth_streaming_moov
    Bool is_smooth = gf_isom_is_smooth_streaming_moov(isom_file);

    // Fuzz gf_isom_is_fragmented
    Bool is_fragmented = gf_isom_is_fragmented(isom_file);

    // Fuzz gf_isom_has_keep_utc_times
    Bool has_utc_times = gf_isom_has_keep_utc_times(isom_file);

    // Fuzz gf_isom_has_sync_shadows
    u32 track_number = Size > 0 ? Data[0] : 0; // Use the first byte as a track number
    Bool has_sync_shadows = gf_isom_has_sync_shadows(isom_file, track_number);

    // Fuzz gf_isom_has_sample_dependency
    Bool has_sample_dependency = gf_isom_has_sample_dependency(isom_file, track_number);

    // Cleanup
    free(isom_file);
    return 0;
}