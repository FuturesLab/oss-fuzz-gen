// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_sample_get_subsamples_buffer at isom_read.c:4866:5 in isomedia.h
// gf_isom_get_mpegh_compatible_profiles at isom_read.c:6215:11 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_add_uuid at isom_write.c:6258:8 in isomedia.h
// gf_isom_text_get_encoded_tx3g at tx3g.c:950:8 in isomedia.h
// gf_isom_get_brand_info at isom_read.c:2631:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void fuzz_gf_isom_sample_get_subsamples_buffer(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 8) return; // Ensure enough data for trackNumber and sampleNumber

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)(Data + 4);
    u32 osize = 0;

    u8 *buffer = gf_isom_sample_get_subsamples_buffer(isom_file, trackNumber, sampleNumber, &osize);
    if (buffer) {
        free(buffer);
    }
}

static void fuzz_gf_isom_get_mpegh_compatible_profiles(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 8) return; // Ensure enough data for trackNumber and sampleDescriptionIndex

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 nb_compatible_profiles = 0;

    const u8 *profiles = gf_isom_get_mpegh_compatible_profiles(isom_file, trackNumber, sampleDescriptionIndex, &nb_compatible_profiles);
    // profiles is a pointer to internal data, no need to free
}

static void fuzz_gf_isom_cenc_get_sample_aux_info(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 12) return; // Ensure enough data for trackNumber, sampleNumber, and sampleDescIndex

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)(Data + 4);
    u32 sampleDescIndex = *(u32 *)(Data + 8);
    u32 container_type = 0; // Random initialization
    u8 *out_buffer = NULL;
    u32 outSize = 0;

    GF_Err err = gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);
    if (out_buffer) {
        free(out_buffer);
    }
}

static void fuzz_gf_isom_add_uuid(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 20) return; // Ensure enough data for trackNumber, UUID, and size

    u32 trackNumber = *(u32 *)Data;
    bin128 UUID;
    memcpy(UUID, Data + 4, sizeof(bin128));
    const u8 *data = (Size > 20) ? (Data + 20) : NULL;
    u32 dataSize = (Size > 20) ? (Size - 20) : 0;

    GF_Err err = gf_isom_add_uuid(isom_file, trackNumber, UUID, data, dataSize);
}

static void fuzz_gf_isom_text_get_encoded_tx3g(GF_ISOFile *isom_file, const uint8_t *Data, size_t Size) {
    if (Size < 12) return; // Ensure enough data for trackNumber, sampleDescriptionIndex, and sidx_offset

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u32 sidx_offset = *(u32 *)(Data + 8);
    u8 *tx3g = NULL;
    u32 tx3g_size = 0;

    GF_Err err = gf_isom_text_get_encoded_tx3g(isom_file, trackNumber, sampleDescriptionIndex, sidx_offset, &tx3g, &tx3g_size);
    if (tx3g) {
        free(tx3g);
    }
}

static void fuzz_gf_isom_get_brand_info(GF_ISOFile *isom_file) {
    u32 brand = 0;
    u32 minorVersion = 0;
    u32 AlternateBrandsCount = 0;

    GF_Err err = gf_isom_get_brand_info(isom_file, &brand, &minorVersion, &AlternateBrandsCount);
}

int LLVMFuzzerTestOneInput_172(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = NULL;

    // Create a dummy file to simulate the ISO file input
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file as an ISO file
    isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Fuzz various functions
    fuzz_gf_isom_sample_get_subsamples_buffer(isom_file, Data, Size);
    fuzz_gf_isom_get_mpegh_compatible_profiles(isom_file, Data, Size);
    fuzz_gf_isom_cenc_get_sample_aux_info(isom_file, Data, Size);
    fuzz_gf_isom_add_uuid(isom_file, Data, Size);
    fuzz_gf_isom_text_get_encoded_tx3g(isom_file, Data, Size);
    fuzz_gf_isom_get_brand_info(isom_file);

    // Cleanup
    gf_isom_close(isom_file);
    remove("./dummy_file");

    return 0;
}