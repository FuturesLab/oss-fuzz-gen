// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_segment_get_track_fragment_decode_time at isom_read.c:908:5 in isomedia.h
// gf_isom_get_track_duration at isom_read.c:1076:5 in isomedia.h
// gf_isom_get_smooth_next_tfdt at isom_read.c:5835:5 in isomedia.h
// gf_isom_get_sample_dts at isom_read.c:2141:5 in isomedia.h
// gf_isom_get_sample_from_dts at isom_read.c:2168:5 in isomedia.h
// gf_isom_get_current_tfdt at isom_read.c:5822:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u64)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 moof_index = *(u32 *)Data;
    u32 traf_index = *(u32 *)(Data + sizeof(u32));
    u64 decode_time;
    u32 track_id = gf_isom_segment_get_track_fragment_decode_time(isom_file, moof_index, traf_index, &decode_time);

    u32 trackNumber = *(u32 *)(Data + 2 * sizeof(u32));
    u64 track_duration = gf_isom_get_track_duration(isom_file, trackNumber);

    u64 smooth_next_tfdt = gf_isom_get_smooth_next_tfdt(isom_file, trackNumber);

    u32 sampleNumber = *(u32 *)(Data + 3 * sizeof(u32));
    u64 sample_dts = gf_isom_get_sample_dts(isom_file, trackNumber, sampleNumber);

    u64 dts = *(u64 *)(Data + 4 * sizeof(u32));
    u32 sample_from_dts = gf_isom_get_sample_from_dts(isom_file, trackNumber, dts);

    u64 current_tfdt = gf_isom_get_current_tfdt(isom_file, trackNumber);

    gf_isom_close(isom_file);

    return 0;
}