// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_make_interleave at isom_write.c:6051:8 in isomedia.h
// gf_isom_freeze_order at isom_read.c:76:8 in isomedia.h
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_disable_brand_rewrite at isom_write.c:3512:8 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for GF_ISOFile, assuming it is large enough for the testing purpose
    GF_ISOFile* file = (GF_ISOFile*)malloc(1024); // Arbitrary size for fuzzing
    if (!file) return NULL;
    memset(file, 0, 1024); // Initialize allocated memory to zero
    return file;
}

static void cleanup_iso_file(GF_ISOFile* file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_296(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Double)) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    Double time_in_sec;
    memcpy(&time_in_sec, Data, sizeof(Double));

    // Fuzz gf_isom_make_interleave
    gf_isom_make_interleave(iso_file, time_in_sec);

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(iso_file);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(iso_file);

    // Fuzz gf_isom_disable_brand_rewrite
    Bool do_disable = (Size > sizeof(Double)) ? Data[sizeof(Double)] % 2 : 0;
    gf_isom_disable_brand_rewrite(iso_file, do_disable);

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(iso_file);

    // Fuzz gf_isom_enable_mfra
    gf_isom_enable_mfra(iso_file);

    cleanup_iso_file(iso_file);

    return 0;
}