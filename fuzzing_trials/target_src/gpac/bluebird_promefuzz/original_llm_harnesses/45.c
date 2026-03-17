// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_keep_utc_times at isom_read.c:5543:6 in isomedia.h
// gf_isom_is_inplace_rewrite at isom_write.c:9035:6 in isomedia.h
// gf_isom_is_smooth_streaming_moov at isom_read.c:5848:6 in isomedia.h
// gf_isom_has_movie at isom_read.c:835:6 in isomedia.h
// gf_isom_is_fragmented at movie_fragments.c:3523:6 in isomedia.h
// gf_isom_is_JPEG2000 at isom_read.c:4270:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

// Define a size for the dummy structure, assuming a reasonable size
#define DUMMY_ISO_FILE_SIZE 1024

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for GF_ISOFile with a dummy size
    GF_ISOFile *file = (GF_ISOFile *)malloc(DUMMY_ISO_FILE_SIZE);
    if (!file) return NULL;
    memset(file, 0, DUMMY_ISO_FILE_SIZE);
    return file;
}

static void destroy_dummy_iso_file(GF_ISOFile *file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least one byte for meaningful operations

    GF_ISOFile *isoFile = create_dummy_iso_file();
    if (!isoFile) return 0;

    // Fuzz gf_isom_keep_utc_times
    Bool keep_utc = Data[0] % 2; // Use the first byte for boolean
    gf_isom_keep_utc_times(isoFile, keep_utc);

    // Fuzz gf_isom_is_inplace_rewrite
    Bool inplace_rewrite = gf_isom_is_inplace_rewrite(isoFile);

    // Fuzz gf_isom_is_smooth_streaming_moov
    Bool is_smooth_streaming = gf_isom_is_smooth_streaming_moov(isoFile);

    // Fuzz gf_isom_has_movie
    Bool has_movie = gf_isom_has_movie(isoFile);

    // Fuzz gf_isom_is_fragmented
    Bool is_fragmented = gf_isom_is_fragmented(isoFile);

    // Fuzz gf_isom_is_JPEG2000
    Bool is_jpeg2000 = gf_isom_is_JPEG2000(isoFile);

    // Cleanup
    destroy_dummy_iso_file(isoFile);

    return 0;
}