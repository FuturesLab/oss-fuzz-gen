#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Create a dummy ISOFile structure
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return NULL;

    // Additional initialization can be done here if necessary

    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    // Write input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    // Extract track number and sample description index from the input data
    u32 trackNumber = *(u32*)Data;
    u32 sampleDescriptionIndex = (Size >= 2 * sizeof(u32)) ? *(u32*)(Data + sizeof(u32)) : 0;

    // Test gf_isom_vp_config_get
    GF_VPConfig *vp_config = gf_isom_vp_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (vp_config) {
        free(vp_config); // Free the returned config if not NULL
    }

    // Test gf_isom_get_max_sample_delta
    u32 max_sample_delta = gf_isom_get_max_sample_delta(isom_file, trackNumber);

    // Test gf_isom_get_sync_point_count
    u32 sync_point_count = gf_isom_get_sync_point_count(isom_file, trackNumber);

    // Test gf_isom_get_avg_sample_delta
    u32 avg_sample_delta = gf_isom_get_avg_sample_delta(isom_file, trackNumber);

    // Test gf_isom_get_constant_sample_size
    u32 constant_sample_size = gf_isom_get_constant_sample_size(isom_file, trackNumber);

    // Test gf_isom_get_track_id
    GF_ISOTrackID track_id = gf_isom_get_track_id(isom_file, trackNumber);

    cleanup_iso_file(isom_file);
    return 0;
}