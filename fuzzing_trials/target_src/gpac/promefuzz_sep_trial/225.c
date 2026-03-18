// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_sample_get_subsamples_buffer at isom_read.c:4866:5 in isomedia.h
// gf_isom_get_brand_info at isom_read.c:2631:8 in isomedia.h
// gf_isom_add_uuid at isom_write.c:6258:8 in isomedia.h
// gf_isom_text_get_encoded_tx3g at tx3g.c:950:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_get_mpegh_compatible_profiles at isom_read.c:6215:11 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_225(const uint8_t *Data, size_t Size) {
    // Initialize a dummy ISO file
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Initialize variables for API functions
    u32 trackNumber = 1;
    u32 sampleNumber = 1;
    u32 osize = 0;
    u32 brand = 0;
    u32 minorVersion = 0;
    u32 AlternateBrandsCount = 0;
    bin128 UUID = {0};
    u8 *buffer = NULL;
    u8 *tx3g = NULL;
    u32 tx3g_size = 0;
    u32 container_type = 0;
    u32 nb_compatible_profiles = 0;

    // Call gf_isom_sample_get_subsamples_buffer
    buffer = gf_isom_sample_get_subsamples_buffer(isom_file, trackNumber, sampleNumber, &osize);
    free(buffer);

    // Call gf_isom_get_brand_info
    gf_isom_get_brand_info(isom_file, &brand, &minorVersion, &AlternateBrandsCount);

    // Call gf_isom_add_uuid
    gf_isom_add_uuid(isom_file, trackNumber, UUID, Data, Size);

    // Call gf_isom_text_get_encoded_tx3g
    gf_isom_text_get_encoded_tx3g(isom_file, trackNumber, 1, 0, &tx3g, &tx3g_size);
    free(tx3g);

    // Call gf_isom_cenc_get_sample_aux_info
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, 1, &container_type, &buffer, &osize);
    free(buffer);

    // Call gf_isom_get_mpegh_compatible_profiles
    const u8 *profiles = gf_isom_get_mpegh_compatible_profiles(isom_file, trackNumber, 1, &nb_compatible_profiles);
    (void)profiles; // To avoid unused variable warning

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}