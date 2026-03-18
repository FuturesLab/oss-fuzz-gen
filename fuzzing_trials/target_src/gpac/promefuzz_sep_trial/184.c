// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
// gf_isom_add_desc_to_root_od at isom_write.c:413:8 in isomedia.h
// gf_isom_add_desc_to_description at isom_write.c:1631:8 in isomedia.h
// gf_isom_get_root_od at isom_read.c:659:16 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_delete at isom_read.c:2899:6 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assuming a function exists to create a GF_ISOFile in the actual library
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static GF_Descriptor* create_dummy_descriptor() {
    // Allocate a larger buffer to avoid buffer overflow
    GF_Descriptor *desc = (GF_Descriptor *)malloc(sizeof(GF_Descriptor) + 100);
    if (!desc) return NULL;
    memset(desc, 0, sizeof(GF_Descriptor) + 100);
    return desc;
}

int LLVMFuzzerTestOneInput_184(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    GF_Descriptor *desc = create_dummy_descriptor();
    if (!desc) {
        gf_isom_delete(isom_file);
        return 0;
    }

    // Fuzz gf_isom_add_desc_to_root_od
    gf_isom_add_desc_to_root_od(isom_file, desc);

    // Fuzz gf_isom_add_desc_to_description
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    gf_isom_add_desc_to_description(isom_file, trackNumber, sampleDescriptionIndex, desc);

    // Fuzz gf_isom_get_root_od
    GF_Descriptor *root_od = gf_isom_get_root_od(isom_file);
    if (root_od) free(root_od); // Caller must destroy the descriptor

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(isom_file);

    // Fuzz gf_isom_enable_mfra
    gf_isom_enable_mfra(isom_file);

    // Clean up
    gf_isom_delete(isom_file);
    free(desc);

    return 0;
}