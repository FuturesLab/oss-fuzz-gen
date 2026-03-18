// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_media_original_duration at isom_read.c:1448:5 in isomedia.h
// gf_isom_get_track_magic at isom_read.c:6160:5 in isomedia.h
// gf_isom_get_media_duration at isom_read.c:1426:5 in isomedia.h
// gf_isom_get_track_duration_orig at isom_read.c:1092:5 in isomedia.h
// gf_isom_get_current_tfdt at isom_read.c:5822:5 in isomedia.h
// gf_isom_get_media_data_size at isom_read.c:4131:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

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

int LLVMFuzzerTestOneInput_180(const uint8_t *Data, size_t Size) {
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