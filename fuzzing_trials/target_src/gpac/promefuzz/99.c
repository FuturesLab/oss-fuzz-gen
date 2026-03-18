// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_has_movie at isom_read.c:835:6 in isomedia.h
// gf_isom_disable_odf_conversion at isom_read.c:652:6 in isomedia.h
// gf_isom_is_single_av at isom_read.c:4218:6 in isomedia.h
// gf_isom_needs_layer_reconstruction at isom_read.c:5516:6 in isomedia.h
// gf_isom_is_smooth_streaming_moov at isom_read.c:5848:6 in isomedia.h
// gf_isom_moov_first at isom_read.c:4964:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    // Create a dummy ISO file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file using gpac API
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = create_dummy_iso_file(Data, Size);
    if (!iso_file) return 0;

    // Test gf_isom_has_movie
    Bool has_movie = gf_isom_has_movie(iso_file);

    // Test gf_isom_disable_odf_conversion
    gf_isom_disable_odf_conversion(iso_file, (Size > 3 && Data[3] % 2 == 0) ? GF_TRUE : GF_FALSE);

    // Test gf_isom_is_single_av
    Bool is_single_av = gf_isom_is_single_av(iso_file);

    // Test gf_isom_needs_layer_reconstruction
    Bool needs_reconstruction = gf_isom_needs_layer_reconstruction(iso_file);

    // Test gf_isom_is_smooth_streaming_moov
    Bool is_smooth_streaming = gf_isom_is_smooth_streaming_moov(iso_file);

    // Test gf_isom_moov_first
    Bool moov_first = gf_isom_moov_first(iso_file);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}