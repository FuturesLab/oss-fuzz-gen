// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_fragment_original_duration at movie_fragments.c:3171:8 in isomedia.h
// gf_isom_set_media_timescale at isom_write.c:5276:8 in isomedia.h
// gf_isom_remove_track at isom_write.c:2942:8 in isomedia.h
// gf_isom_set_ctts_v1 at isom_write.c:7867:8 in isomedia.h
// gf_isom_get_udts_config at sample_descs.c:1070:8 in isomedia.h
// gf_isom_get_pixel_aspect_ratio at isom_read.c:3946:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_292(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 6) return 0;

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 new_timescale = *(u32 *)(Data + 4);
    u32 new_tsinc = *(u32 *)(Data + 8);
    u32 force_rescale_type = *(u32 *)(Data + 12);
    u32 orig_dur = *(u32 *)(Data + 16);
    u32 elapsed_dur = *(u32 *)(Data + 20);
    GF_UDTSConfig cfg;
    u32 hSpacing, vSpacing;

    // Fuzz gf_isom_set_fragment_original_duration
    gf_isom_set_fragment_original_duration(isom_file, trackNumber, orig_dur, elapsed_dur);

    // Fuzz gf_isom_set_media_timescale
    gf_isom_set_media_timescale(isom_file, trackNumber, new_timescale, new_tsinc, force_rescale_type);

    // Fuzz gf_isom_remove_track
    gf_isom_remove_track(isom_file, trackNumber);

    // Fuzz gf_isom_set_ctts_v1
    gf_isom_set_ctts_v1(isom_file, trackNumber, new_tsinc);

    // Fuzz gf_isom_get_udts_config
    gf_isom_get_udts_config(isom_file, trackNumber, 1, &cfg);

    // Fuzz gf_isom_get_pixel_aspect_ratio
    gf_isom_get_pixel_aspect_ratio(isom_file, trackNumber, 1, &hSpacing, &vSpacing);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}