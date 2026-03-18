// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_reset_switch_parameters at isom_write.c:7015:8 in isomedia.h
// gf_isom_set_sample_group_in_traf at isom_write.c:8537:8 in isomedia.h
// gf_isom_remove_root_od at isom_write.c:165:8 in isomedia.h
// gf_isom_set_byte_offset at isom_read.c:5910:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_set_storage_mode at isom_write.c:2636:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for the GF_ISOFile structure using a hypothetical size
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(1024); // Assuming 1024 as a placeholder size
    if (!isom_file) return NULL;

    // Initialize the memory block to zero
    memset(isom_file, 0, 1024); // Using the same hypothetical size
    return isom_file;
}

static void destroy_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_187(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(s64) + sizeof(GF_ISOStorageMode)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    // Fuzz gf_isom_reset_switch_parameters
    gf_isom_reset_switch_parameters(isom_file);

    // Fuzz gf_isom_set_sample_group_in_traf
    gf_isom_set_sample_group_in_traf(isom_file);

    // Fuzz gf_isom_remove_root_od
    gf_isom_remove_root_od(isom_file);

    // Fuzz gf_isom_set_byte_offset
    s64 byte_offset = *(s64 *)Data;
    Data += sizeof(s64);
    Size -= sizeof(s64);
    gf_isom_set_byte_offset(isom_file, byte_offset);

    // Fuzz gf_isom_enable_mfra
    gf_isom_enable_mfra(isom_file);

    // Fuzz gf_isom_set_storage_mode
    GF_ISOStorageMode storage_mode = *(GF_ISOStorageMode *)Data;
    gf_isom_set_storage_mode(isom_file, storage_mode);

    destroy_dummy_iso_file(isom_file);
    return 0;
}