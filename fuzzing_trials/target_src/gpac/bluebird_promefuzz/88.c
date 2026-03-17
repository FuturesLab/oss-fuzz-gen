#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // We assume a dummy allocation size for fuzzing purposes.
    size_t dummy_size = 1024; // Arbitrary size for the dummy allocation
    GF_ISOFile* isoFile = (GF_ISOFile*)malloc(dummy_size);
    if (!isoFile) return NULL;
    memset(isoFile, 0, dummy_size);
    return isoFile;
}

static void cleanup_iso_file(GF_ISOFile* isoFile) {
    if (isoFile) {
        free(isoFile);
    }
}

int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) {
        // Not enough data to extract trackNumber and sampleNumber
        return 0;
    }

    GF_ISOFile* isoFile = create_dummy_iso_file();
    if (!isoFile) return 0;

    u32 trackNumber = *(u32*)Data;
    u32 sampleNumber = *((u32*)Data + 1);
    u32 pack_num_samples = *((u32*)Data + 2);

    // Test gf_isom_is_track_fragmented
    gf_isom_is_track_fragmented(isoFile, trackNumber);

    // Test gf_isom_has_sync_shadows
    gf_isom_has_sync_shadows(isoFile, trackNumber);

    // Test gf_isom_has_sample_dependency
    gf_isom_has_sample_dependency(isoFile, trackNumber);

    // Test gf_isom_get_sample_sync
    gf_isom_get_sample_sync(isoFile, trackNumber, sampleNumber);

    // Test gf_isom_enable_raw_pack
    gf_isom_enable_raw_pack(isoFile, trackNumber, pack_num_samples);

    // Test gf_isom_is_track_encrypted
    gf_isom_is_track_encrypted(isoFile, trackNumber);

    cleanup_iso_file(isoFile);
    return 0;
}