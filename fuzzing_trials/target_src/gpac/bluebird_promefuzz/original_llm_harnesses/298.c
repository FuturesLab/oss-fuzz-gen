// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_iamf_config_get at avc_ext.c:2668:14 in isomedia.h
// gf_isom_get_last_created_track_id at isom_write.c:596:15 in isomedia.h
// gf_isom_get_constant_sample_size at isom_read.c:1780:5 in isomedia.h
// gf_isom_get_track_id at isom_read.c:796:15 in isomedia.h
// gf_isom_get_brands at isom_read.c:2657:12 in isomedia.h
// gf_isom_set_default_sync_track at isom_read.c:4209:6 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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

int LLVMFuzzerTestOneInput_298(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    // Prepare the environment
    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *(((u32 *)Data) + 1);

    // Test gf_isom_iamf_config_get
    GF_IAConfig *config = gf_isom_iamf_config_get(isom_file, trackNumber, sampleDescriptionIndex);
    if (config) {
        // Clean up the config if it was allocated
        free(config);
    }

    // Test gf_isom_get_last_created_track_id
    GF_ISOTrackID lastTrackID = gf_isom_get_last_created_track_id(isom_file);

    // Test gf_isom_get_constant_sample_size
    u32 sampleSize = gf_isom_get_constant_sample_size(isom_file, trackNumber);

    // Test gf_isom_get_track_id
    GF_ISOTrackID trackID = gf_isom_get_track_id(isom_file, trackNumber);

    // Test gf_isom_get_brands
    const u32 *brands = gf_isom_get_brands(isom_file);

    // Test gf_isom_set_default_sync_track
    gf_isom_set_default_sync_track(isom_file, trackNumber);

    // Clean up ISO file
    gf_isom_close(isom_file);

    return 0;
}