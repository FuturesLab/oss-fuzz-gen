// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_release_segment at isom_read.c:3459:8 in isomedia.h
// gf_isom_remove_root_od at isom_write.c:165:8 in isomedia.h
// gf_isom_clone_pl_indications at isom_write.c:3891:8 in isomedia.h
// gf_isom_set_removed_bytes at isom_read.c:3185:8 in isomedia.h
// gf_isom_make_interleave_ex at isom_write.c:6032:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = NULL;
    GF_ISOFile *orig_file = NULL;
    GF_ISOFile *dest_file = NULL;
    GF_Fraction fraction;
    u64 bytes_removed;
    Bool reset_tables;
    GF_Err err;

    // Use the first byte of data to determine boolean values
    reset_tables = (Size > 0) ? (Data[0] % 2) : 0;

    // Use the first 8 bytes of data for bytes_removed if available
    if (Size >= 8) {
        bytes_removed = *((u64 *)Data);
    } else {
        bytes_removed = 0;
    }

    // Use the next 8 bytes for fraction if available
    if (Size >= 16) {
        fraction.num = *((u32 *)(Data + 8));
        fraction.den = *((u32 *)(Data + 12));
    } else {
        fraction.num = 1;
        fraction.den = 1;
    }

    // Call target functions
    err = gf_isom_last_error(isom_file);
    err = gf_isom_release_segment(isom_file, reset_tables);
    err = gf_isom_remove_root_od(isom_file);
    err = gf_isom_clone_pl_indications(orig_file, dest_file);
    err = gf_isom_set_removed_bytes(isom_file, bytes_removed);
    err = gf_isom_make_interleave_ex(isom_file, &fraction);

    return 0;
}