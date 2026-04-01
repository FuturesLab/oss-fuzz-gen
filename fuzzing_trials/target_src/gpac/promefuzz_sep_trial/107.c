// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_freeze_order at isom_read.c:76:8 in isomedia.h
// gf_isom_switch_source at isom_read.c:6717:8 in isomedia.h
// gf_isom_set_root_od_url at isom_write.c:567:8 in isomedia.h
// gf_isom_start_segment at movie_fragments.c:2515:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_refresh_fragmented at isom_read.c:3088:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

// Dummy structure to allocate memory for GF_ISOFile
struct __tag_isom {
    char *fileName;
};

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file structure with minimal initialization
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(sizeof(GF_ISOFile));
    if (!isom_file) return NULL;

    memset(isom_file, 0, sizeof(GF_ISOFile));
    isom_file->fileName = strdup("./dummy_file");

    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file->fileName);
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least one byte for URL strings

    // Prepare the environment
    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    char *url = (char *)malloc(Size + 1);
    if (!url) {
        cleanup_iso_file(isom_file);
        return 0;
    }
    memcpy(url, Data, Size);
    url[Size] = '\0';

    u64 MissingBytes = 0;
    Bool memory_mode = Size % 2;
    const char *SegName = (Size % 3) ? "_gpac_isobmff_redirect" : NULL;

    // Invoke the target functions
    gf_isom_freeze_order(isom_file);
    gf_isom_switch_source(isom_file, url);
    gf_isom_set_root_od_url(isom_file, url);
    gf_isom_start_segment(isom_file, SegName, memory_mode);
    gf_isom_enable_mfra(isom_file);
    gf_isom_refresh_fragmented(isom_file, &MissingBytes, url);

    // Cleanup
    free(url);
    cleanup_iso_file(isom_file);

    return 0;
}