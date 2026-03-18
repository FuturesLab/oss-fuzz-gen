// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_sdp_clean at hint_track.c:884:8 in isomedia.h
// gf_isom_add_desc_to_root_od at isom_write.c:413:8 in isomedia.h
// gf_isom_release_segment at isom_read.c:3459:8 in isomedia.h
// gf_isom_flush_fragments at movie_fragments.c:1468:8 in isomedia.h
// gf_isom_set_byte_offset at isom_read.c:5910:8 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for the GF_ISOFile using a reasonable size
    GF_ISOFile *iso_file = (GF_ISOFile *)malloc(1024); // Assuming 1024 bytes is enough
    if (!iso_file) return NULL;
    memset(iso_file, 0, 1024);
    return iso_file;
}

static GF_Descriptor* create_dummy_descriptor() {
    GF_Descriptor *desc = (GF_Descriptor *)malloc(sizeof(GF_Descriptor));
    if (!desc) return NULL;
    memset(desc, 0, sizeof(GF_Descriptor));
    return desc;
}

int LLVMFuzzerTestOneInput_169(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    GF_Descriptor *desc = create_dummy_descriptor();
    if (!desc) {
        free(iso_file);
        return 0;
    }

    // Fuzz gf_isom_sdp_clean
    gf_isom_sdp_clean(iso_file);

    // Fuzz gf_isom_add_desc_to_root_od
    gf_isom_add_desc_to_root_od(iso_file, desc);

    // Fuzz gf_isom_release_segment
    Bool reset_tables = (Size > 0) ? Data[0] % 2 : 0;
    gf_isom_release_segment(iso_file, reset_tables);

    // Fuzz gf_isom_flush_fragments
    Bool last_segment = (Size > 1) ? Data[1] % 2 : 0;
    gf_isom_flush_fragments(iso_file, last_segment);

    // Ensure there is enough data to read a 64-bit integer
    s64 byte_offset = 0;
    if (Size >= sizeof(s64) + 2) {
        memcpy(&byte_offset, Data + 2, sizeof(s64));
    }
    gf_isom_set_byte_offset(iso_file, byte_offset);

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(iso_file);

    // Cleanup
    free(desc);
    free(iso_file);

    return 0;
}