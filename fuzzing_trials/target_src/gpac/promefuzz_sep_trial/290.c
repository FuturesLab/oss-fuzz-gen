// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_fragment_original_duration at movie_fragments.c:3171:8 in isomedia.h
// gf_isom_get_pixel_aspect_ratio at isom_read.c:3946:8 in isomedia.h
// gf_isom_get_visual_info at isom_read.c:3821:8 in isomedia.h
// gf_isom_set_ctts_v1 at isom_write.c:7867:8 in isomedia.h
// gf_isom_copy_sample_info at isom_write.c:8078:8 in isomedia.h
// gf_isom_get_udts_config at sample_descs.c:1070:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void setup_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_290(const uint8_t *Data, size_t Size) {
    // Ensure there is enough data for all required operations
    if (Size < 6 * sizeof(u32)) return 0;

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    GF_ISOTrackID TrackID = *(u32 *)(Data);
    u32 orig_dur = *(u32 *)(Data + sizeof(GF_ISOTrackID));
    u32 elapsed_dur = *(u32 *)(Data + sizeof(GF_ISOTrackID) + sizeof(u32));
    u32 trackNumber = *(u32 *)(Data + sizeof(GF_ISOTrackID) + 2 * sizeof(u32));
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(GF_ISOTrackID) + 3 * sizeof(u32));

    u32 hSpacing, vSpacing, Width, Height, ctts_shift, sampleNumber;
    GF_UDTSConfig cfg;

    setup_dummy_file(Data, Size);

    // Test gf_isom_set_fragment_original_duration
    gf_isom_set_fragment_original_duration(isom_file, TrackID, orig_dur, elapsed_dur);

    // Test gf_isom_get_pixel_aspect_ratio
    gf_isom_get_pixel_aspect_ratio(isom_file, trackNumber, sampleDescriptionIndex, &hSpacing, &vSpacing);

    // Test gf_isom_get_visual_info
    gf_isom_get_visual_info(isom_file, trackNumber, sampleDescriptionIndex, &Width, &Height);

    // Test gf_isom_set_ctts_v1
    ctts_shift = *(u32 *)(Data + sizeof(GF_ISOTrackID) + 4 * sizeof(u32));
    gf_isom_set_ctts_v1(isom_file, trackNumber, ctts_shift);

    // Ensure there is enough data for sampleNumber
    if (Size >= sizeof(GF_ISOTrackID) + 6 * sizeof(u32)) {
        sampleNumber = *(u32 *)(Data + sizeof(GF_ISOTrackID) + 5 * sizeof(u32));
        // Test gf_isom_copy_sample_info
        gf_isom_copy_sample_info(isom_file, trackNumber, isom_file, trackNumber, sampleNumber);
    }

    // Test gf_isom_get_udts_config
    gf_isom_get_udts_config(isom_file, trackNumber, sampleDescriptionIndex, &cfg);

    gf_isom_close(isom_file);
    return 0;
}