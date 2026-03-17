// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_reset_alt_brands_ex at isom_write.c:3646:8 in isomedia.h
// gf_isom_remove_meta_item at meta.c:1879:8 in isomedia.h
// gf_isom_disable_brand_rewrite at isom_write.c:3512:8 in isomedia.h
// gf_isom_force_64bit_chunk_offset at isom_write.c:2669:8 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
// gf_isom_reset_track_switch_parameter at isom_write.c:6989:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Assuming the third argument is a temporary directory, we pass NULL for default behavior.
    GF_ISOFile* isofile = gf_isom_open("./dummy_file", GF_ISOM_WRITE_EDIT, NULL);
    if (!isofile) return NULL;
    return isofile;
}

static void cleanup_isofile(GF_ISOFile* isofile) {
    if (isofile) {
        // Assuming the library provides a function to close or free the ISO file
        gf_isom_close(isofile);
    }
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile* isofile = create_dummy_isofile();
    if (!isofile) return 0;

    // Fuzz gf_isom_reset_alt_brands_ex
    Bool leave_empty = Data[0] % 2;
    gf_isom_reset_alt_brands_ex(isofile, leave_empty);

    // Fuzz gf_isom_remove_meta_item
    Bool root_meta = Data[0] % 2;
    u32 track_num = (Size > 1) ? Data[1] : 0;
    u32 item_num = (Size > 2) ? Data[2] : 0;
    Bool keep_refs = (Size > 3) ? Data[3] % 2 : 0;
    const char *keep_props = (Size > 4) ? (const char*)&Data[4] : NULL;
    gf_isom_remove_meta_item(isofile, root_meta, track_num, item_num, keep_refs, keep_props);

    // Fuzz gf_isom_disable_brand_rewrite
    Bool do_disable = Data[0] % 2;
    gf_isom_disable_brand_rewrite(isofile, do_disable);

    // Fuzz gf_isom_force_64bit_chunk_offset
    Bool set_on = Data[0] % 2;
    gf_isom_force_64bit_chunk_offset(isofile, set_on);

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(isofile);

    // Fuzz gf_isom_reset_track_switch_parameter
    u32 trackNumber = (Size > 1) ? Data[1] : 0;
    Bool reset_all_group = (Size > 2) ? Data[2] % 2 : 0;
    gf_isom_reset_track_switch_parameter(isofile, trackNumber, reset_all_group);

    cleanup_isofile(isofile);
    return 0;
}