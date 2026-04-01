// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_force_track_duration at isom_write.c:896:8 in isomedia.h
// gf_isom_patch_last_sample_duration at isom_write.c:1425:8 in isomedia.h
// gf_isom_get_fragmented_samples_info at isom_read.c:5436:8 in isomedia.h
// gf_isom_set_traf_base_media_decode_time at movie_fragments.c:3443:8 in isomedia.h
// gf_isom_set_track_creation_time at isom_write.c:230:8 in isomedia.h
// gf_isom_set_media_creation_time at isom_write.c:242:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + sizeof(u64)) {
        return 0;
    }

    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ_DUMP, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32*)Data;
    u64 duration = *(u64*)(Data + sizeof(u32));

    // Fuzz gf_isom_force_track_duration
    gf_isom_force_track_duration(isom_file, trackNumber, duration);

    // Fuzz gf_isom_patch_last_sample_duration
    gf_isom_patch_last_sample_duration(isom_file, trackNumber, duration);

    // Fuzz gf_isom_get_fragmented_samples_info
    u32 nb_samples = 0;
    u64 total_duration = 0;
    gf_isom_get_fragmented_samples_info(isom_file, trackNumber, &nb_samples, &total_duration);

    // Fuzz gf_isom_set_traf_base_media_decode_time
    gf_isom_set_traf_base_media_decode_time(isom_file, trackNumber, duration);

    // Fuzz gf_isom_set_track_creation_time
    gf_isom_set_track_creation_time(isom_file, trackNumber, duration, duration);

    // Fuzz gf_isom_set_media_creation_time
    gf_isom_set_media_creation_time(isom_file, trackNumber, duration, duration);

    gf_isom_close(isom_file);

    return 0;
}