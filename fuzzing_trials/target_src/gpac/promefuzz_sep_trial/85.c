// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_keep_utc_times at isom_read.c:5543:6 in isomedia.h
// gf_isom_needs_layer_reconstruction at isom_read.c:5516:6 in isomedia.h
// gf_isom_set_single_moof_mode at isom_read.c:3144:6 in isomedia.h
// gf_isom_is_smooth_streaming_moov at isom_read.c:5848:6 in isomedia.h
// gf_isom_is_inplace_rewrite at isom_write.c:9035:6 in isomedia.h
// gf_isom_disable_odf_conversion at isom_read.c:652:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "isomedia.h"

// Assuming a reasonable size for the GF_ISOFile structure for allocation
#define GF_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_isofile() {
    GF_ISOFile* file = (GF_ISOFile*)malloc(GF_ISOFILE_SIZE);
    if (!file) return NULL;
    memset(file, 0, GF_ISOFILE_SIZE);
    return file;
}

static void cleanup_isofile(GF_ISOFile* file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile* isofile = create_dummy_isofile();
    if (!isofile) return 0;

    // Fuzz gf_isom_keep_utc_times
    Bool keep_utc = Data[0] % 2;
    gf_isom_keep_utc_times(isofile, keep_utc);

    // Fuzz gf_isom_needs_layer_reconstruction
    Bool needs_reconstruction = gf_isom_needs_layer_reconstruction(isofile);

    // Fuzz gf_isom_set_single_moof_mode
    Bool single_moof_mode = (Data[0] >> 1) % 2;
    gf_isom_set_single_moof_mode(isofile, single_moof_mode);

    // Fuzz gf_isom_is_smooth_streaming_moov
    Bool is_smooth_streaming = gf_isom_is_smooth_streaming_moov(isofile);

    // Fuzz gf_isom_is_inplace_rewrite
    Bool is_inplace_rewrite = gf_isom_is_inplace_rewrite(isofile);

    // Fuzz gf_isom_disable_odf_conversion
    Bool disable_odf_conversion = (Data[0] >> 2) % 2;
    gf_isom_disable_odf_conversion(isofile, disable_odf_conversion);

    cleanup_isofile(isofile);

    return 0;
}