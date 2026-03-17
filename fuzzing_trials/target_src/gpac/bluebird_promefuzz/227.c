#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

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

int LLVMFuzzerTestOneInput_227(const uint8_t *Data, size_t Size) {
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