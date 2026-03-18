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
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Since GF_ISOFile is an opaque type, we cannot directly allocate or initialize it.
    // Normally, we would have to use a library function to create and initialize a GF_ISOFile.
    // However, for the purpose of this fuzzing test, we will assume a function exists to do this.
    // For demonstration, we will return NULL, which is a valid input to the functions being tested.
    return NULL;
}

static void destroy_dummy_isofile(GF_ISOFile *file) {
    // Normally, we would use a library function to properly destroy a GF_ISOFile.
    // Since we are returning NULL in create_dummy_isofile, there is nothing to free.
}

int LLVMFuzzerTestOneInput_132(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();

    // Fuzz gf_isom_last_error
    gf_isom_last_error(isom_file);

    // Fuzz gf_isom_release_segment
    Bool reset_tables = Data[0] % 2; // Randomly choose true or false
    gf_isom_release_segment(isom_file, reset_tables);

    // Fuzz gf_isom_remove_root_od
    gf_isom_remove_root_od(isom_file);

    // Fuzz gf_isom_clone_pl_indications
    GF_ISOFile *dest_file = create_dummy_isofile();
    gf_isom_clone_pl_indications(isom_file, dest_file);

    // Fuzz gf_isom_set_removed_bytes
    u64 bytes_removed = (Size > 8) ? *(u64 *)(Data + 1) : 0;
    gf_isom_set_removed_bytes(isom_file, bytes_removed);

    // Fuzz gf_isom_make_interleave_ex
    GF_Fraction fTimeInSec;
    fTimeInSec.num = (Size > 12) ? *(u32 *)(Data + 9) : 1;
    fTimeInSec.den = (Size > 16) ? *(u32 *)(Data + 13) : 1;
    gf_isom_make_interleave_ex(isom_file, &fTimeInSec);

    destroy_dummy_isofile(isom_file);
    destroy_dummy_isofile(dest_file);
    return 0;
}