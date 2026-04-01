// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_append_edit at isom_write.c:2849:8 in isomedia.h
// gf_isom_set_track_magic at isom_write.c:8936:8 in isomedia.h
// gf_isom_set_traf_mss_timeext at movie_fragments.c:2563:8 in isomedia.h
// gf_isom_modify_edit at isom_write.c:2894:8 in isomedia.h
// gf_isom_set_traf_base_media_decode_time at movie_fragments.c:3443:8 in isomedia.h
// gf_isom_set_fragment_reference_time at movie_fragments.c:2552:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* open_dummy_iso_file() {
    // Create a dummy file to simulate ISO file operations
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fclose(file);

    // Open the dummy file using gpac's ISO file opening function
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void close_dummy_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_215(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = open_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u64 EditDuration = (Size > 8) ? *(u64 *)(Data + 1) : 0;
    u64 MediaTime = (Size > 16) ? *(u64 *)(Data + 9) : 0;
    GF_ISOEditType EditMode = (GF_ISOEditType)((Size > 17) ? Data[17] : 0);
    u64 magic = (Size > 25) ? *(u64 *)(Data + 18) : 0;
    GF_ISOTrackID reference_track_ID = (Size > 26) ? *(u32 *)(Data + 26) : 0;
    u64 decode_traf_time = (Size > 34) ? *(u64 *)(Data + 30) : 0;
    u64 traf_duration = (Size > 42) ? *(u64 *)(Data + 38) : 0;
    u32 edit_index = (Size > 46) ? *(u32 *)(Data + 46) : 0;
    u64 decode_time = (Size > 54) ? *(u64 *)(Data + 50) : 0;
    u64 ntp = (Size > 62) ? *(u64 *)(Data + 58) : 0;
    u64 timestamp = (Size > 70) ? *(u64 *)(Data + 66) : 0;
    Bool at_mux = (Size > 71) ? Data[71] & 1 : 0;

    gf_isom_append_edit(isom_file, trackNumber, EditDuration, MediaTime, EditMode);
    gf_isom_set_track_magic(isom_file, trackNumber, magic);
    gf_isom_set_traf_mss_timeext(isom_file, reference_track_ID, decode_traf_time, traf_duration);
    gf_isom_modify_edit(isom_file, trackNumber, edit_index, EditDuration, MediaTime, EditMode);
    gf_isom_set_traf_base_media_decode_time(isom_file, reference_track_ID, decode_time);
    gf_isom_set_fragment_reference_time(isom_file, reference_track_ID, ntp, timestamp, at_mux);

    close_dummy_iso_file(isom_file);
    return 0;
}