#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

// Define a dummy size for GF_ISOFile since its structure is not fully available
#define DUMMY_GFI_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_isofile() {
    GF_ISOFile *isom_file = (GF_ISOFile*)malloc(DUMMY_GFI_ISOFILE_SIZE);
    if (!isom_file) return NULL;
    memset(isom_file, 0, DUMMY_GFI_ISOFILE_SIZE);
    return isom_file;
}

static void destroy_dummy_isofile(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_228(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    // Use the first byte as a boolean for keep_sample_count
    Bool keep_sample_count = Data[0] % 2;

    // Call gf_isom_reset_fragment_info
    gf_isom_reset_fragment_info(isom_file, keep_sample_count);

    // Call gf_isom_has_keep_utc_times
    Bool has_utc = gf_isom_has_keep_utc_times(isom_file);

    // Use the second byte as a track number
    u32 track_number = (Size > 1) ? Data[1] : 0;

    // Call gf_isom_has_sync_shadows
    Bool has_sync_shadows = gf_isom_has_sync_shadows(isom_file, track_number);

    // Call gf_isom_has_sample_dependency
    Bool has_sample_dependency = gf_isom_has_sample_dependency(isom_file, track_number);

    // Call gf_isom_is_smooth_streaming_moov
    Bool is_smooth_streaming = gf_isom_is_smooth_streaming_moov(isom_file);

    // Call gf_isom_is_fragmented
    Bool is_fragmented = gf_isom_is_fragmented(isom_file);

    // Clean up
    destroy_dummy_isofile(isom_file);

    return 0;
}