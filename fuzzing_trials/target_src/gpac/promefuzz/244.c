// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_freeze_order at isom_read.c:76:8 in isomedia.h
// gf_isom_add_desc_to_root_od at isom_write.c:413:8 in isomedia.h
// gf_isom_reset_data_offset at isom_read.c:3151:8 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Allocate memory for GF_ISOFile using the library's API if available
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!file) return NULL;
    return file;
}

static GF_Descriptor* create_dummy_descriptor() {
    GF_Descriptor *desc = (GF_Descriptor*) malloc(sizeof(GF_Descriptor));
    if (!desc) return NULL;
    // Initialize the descriptor with dummy values
    return desc;
}

int LLVMFuzzerTestOneInput_244(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    // Test gf_isom_freeze_order
    gf_isom_freeze_order(isom_file);

    // Test gf_isom_add_desc_to_root_od
    GF_Descriptor *desc = create_dummy_descriptor();
    if (desc) {
        gf_isom_add_desc_to_root_od(isom_file, desc);
        free(desc);
    }

    // Test gf_isom_reset_data_offset
    u64 top_box_start = 0;
    gf_isom_reset_data_offset(isom_file, &top_box_start);

    // Test gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(isom_file);

    // Test gf_isom_enable_mfra
    gf_isom_enable_mfra(isom_file);

    // Test gf_isom_last_error
    gf_isom_last_error(isom_file);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}