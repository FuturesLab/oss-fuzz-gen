// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open_progressive_ex at isom_read.c:435:8 in isomedia.h
// gf_isom_get_sidx_duration at isom_read.c:6196:8 in isomedia.h
// gf_isom_set_removed_bytes at isom_read.c:3185:8 in isomedia.h
// gf_isom_set_movie_duration at movie_fragments.c:61:8 in isomedia.h
// gf_isom_set_creation_time at isom_write.c:221:8 in isomedia.h
// gf_isom_set_fragment_reference_time at movie_fragments.c:2552:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_313(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = NULL;
    GF_Err err;

    // Attempt to open a dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    u64 sidx_dur = 0;
    u32 sidx_timescale = 0;
    err = gf_isom_open_progressive_ex("./dummy_file", 0, Size, 0, &isom_file, NULL, NULL);
    if (err == GF_OK && isom_file) {
        gf_isom_get_sidx_duration(isom_file, &sidx_dur, &sidx_timescale);

        u64 bytes_removed = Data[0];
        gf_isom_set_removed_bytes(isom_file, bytes_removed);

        u64 duration = Data[0];
        Bool remove_mehd = (Bool)(Data[0] % 2);
        gf_isom_set_movie_duration(isom_file, duration, remove_mehd);

        u64 create_time = Data[0];
        u64 modif_time = Data[0];
        gf_isom_set_creation_time(isom_file, create_time, modif_time);

        GF_ISOTrackID reference_track_ID = Data[0];
        u64 ntp = Data[0];
        u64 timestamp = Data[0];
        Bool at_mux = (Bool)(Data[0] % 2);
        gf_isom_set_fragment_reference_time(isom_file, reference_track_ID, ntp, timestamp, at_mux);

        gf_isom_close(isom_file);
    }

    return 0;
}