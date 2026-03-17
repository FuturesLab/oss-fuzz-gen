#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

// Define a dummy structure with the same size as GF_ISOFile for allocation
typedef struct {
    char dummy[256]; // Adjust size as needed for realistic testing
} DummyISOFile;

static GF_ISOFile* create_dummy_isofile() {
    // Allocate memory for the DummyISOFile structure
    GF_ISOFile *isofile = (GF_ISOFile *)malloc(sizeof(DummyISOFile));
    if (!isofile) return NULL;
    memset(isofile, 0, sizeof(DummyISOFile));
    return isofile;
}

static void cleanup_isofile(GF_ISOFile *isofile) {
    if (isofile) {
        free(isofile);
    }
}

int LLVMFuzzerTestOneInput_203(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    // Create a dummy GF_ISOFile
    GF_ISOFile *isofile = create_dummy_isofile();
    if (!isofile) return 0;

    // Extract track number from input data
    u32 trackNumber = *(u32 *)Data;

    // Invoke target functions
    u64 duration = gf_isom_get_media_original_duration(isofile, trackNumber);
    u64 magic = gf_isom_get_track_magic(isofile, trackNumber);
    u64 media_duration = gf_isom_get_media_duration(isofile, trackNumber);
    u64 track_duration_orig = gf_isom_get_track_duration_orig(isofile, trackNumber);
    u64 tfdt = gf_isom_get_current_tfdt(isofile, trackNumber);
    u64 media_data_size = gf_isom_get_media_data_size(isofile, trackNumber);

    // Use the return values to avoid compiler optimizations
    if (duration || magic || media_duration || track_duration_orig || tfdt || media_data_size) {
        // Do nothing, just prevent optimization
    }

    // Cleanup
    cleanup_isofile(isofile);

    return 0;
}