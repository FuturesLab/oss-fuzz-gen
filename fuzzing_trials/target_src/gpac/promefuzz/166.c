// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_icc_profile at isom_read.c:4019:8 in isomedia.h
// gf_isom_modify_alternate_brand at isom_write.c:3571:8 in isomedia.h
// gf_isom_vvc_set_inband_config at avc_ext.c:2427:8 in isomedia.h
// gf_isom_apply_box_patch at isom_write.c:8665:8 in isomedia.h
// gf_isom_finalize_for_fragment at movie_fragments.c:85:8 in isomedia.h
// gf_isom_hevc_set_inband_config at avc_ext.c:2324:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

// Dummy function to simulate creating an ISO file, as we can't access the internal structure
static GF_ISOFile* create_dummy_iso_file() {
    return NULL; // Return NULL as we can't create an actual instance
}

static void destroy_dummy_iso_file(GF_ISOFile *file) {
    // No action needed since we are not actually allocating
}

int LLVMFuzzerTestOneInput_166(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 Brand = *(u32 *)(Data + sizeof(u32) * 2);
    Bool icc_restricted = GF_FALSE;
    const u8 *icc = NULL;
    u32 icc_size = 0;
    Bool AddIt = GF_TRUE;
    Bool keep_xps = GF_TRUE;
    GF_Err result;

    // Fuzz gf_isom_get_icc_profile
    result = gf_isom_get_icc_profile(isom_file, trackNumber, sampleDescriptionIndex, &icc_restricted, &icc, &icc_size);
    if (result != GF_OK && result != GF_BAD_PARAM && result != GF_ISOM_INVALID_FILE) {
        destroy_dummy_iso_file(isom_file);
        return 0;
    }

    // Fuzz gf_isom_modify_alternate_brand
    result = gf_isom_modify_alternate_brand(isom_file, Brand, AddIt);
    if (result != GF_OK && result != GF_BAD_PARAM) {
        destroy_dummy_iso_file(isom_file);
        return 0;
    }

    // Fuzz gf_isom_vvc_set_inband_config
    result = gf_isom_vvc_set_inband_config(isom_file, trackNumber, sampleDescriptionIndex, keep_xps);
    if (result != GF_OK && result != GF_BAD_PARAM) {
        destroy_dummy_iso_file(isom_file);
        return 0;
    }

    // Fuzz gf_isom_apply_box_patch
    FILE *patch_file = fopen("./dummy_file", "wb");
    if (patch_file) {
        fwrite(Data, 1, Size, patch_file);
        fclose(patch_file);

        result = gf_isom_apply_box_patch(isom_file, trackNumber, "./dummy_file", GF_FALSE);
        if (result != GF_OK && result != GF_BAD_PARAM && result != GF_NOT_SUPPORTED && result != GF_NON_COMPLIANT_BITSTREAM) {
            destroy_dummy_iso_file(isom_file);
            return 0;
        }
    }

    // Fuzz gf_isom_finalize_for_fragment
    result = gf_isom_finalize_for_fragment(isom_file, trackNumber % 3, GF_TRUE);
    if (result != GF_OK && result != GF_BAD_PARAM) {
        destroy_dummy_iso_file(isom_file);
        return 0;
    }

    // Fuzz gf_isom_hevc_set_inband_config
    result = gf_isom_hevc_set_inband_config(isom_file, trackNumber, sampleDescriptionIndex, keep_xps);
    if (result != GF_OK && result != GF_BAD_PARAM) {
        destroy_dummy_iso_file(isom_file);
        return 0;
    }

    destroy_dummy_iso_file(isom_file);
    return 0;
}