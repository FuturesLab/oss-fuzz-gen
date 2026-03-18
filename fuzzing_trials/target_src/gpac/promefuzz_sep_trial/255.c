// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_modify_edit at isom_write.c:2894:8 in isomedia.h
// gf_isom_patch_last_sample_duration at isom_write.c:1425:8 in isomedia.h
// gf_isom_get_edit at isom_read.c:2560:8 in isomedia.h
// gf_isom_set_traf_mss_timeext at movie_fragments.c:2563:8 in isomedia.h
// gf_isom_set_media_creation_time at isom_write.c:242:8 in isomedia.h
// gf_isom_get_chunk_info at isom_read.c:6325:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_255(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u64) * 9) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 edit_index = *(u32 *)(Data + sizeof(u32));
    u64 EditDuration = *(u64 *)(Data + sizeof(u32) * 2);
    u64 MediaTime = *(u64 *)(Data + sizeof(u32) * 2 + sizeof(u64));
    GF_ISOEditType EditMode = *(GF_ISOEditType *)(Data + sizeof(u32) * 2 + sizeof(u64) * 2);

    gf_isom_modify_edit(isom_file, trackNumber, edit_index, EditDuration, MediaTime, EditMode);

    u64 next_dts = *(u64 *)(Data + sizeof(u32) * 2 + sizeof(u64) * 3);
    gf_isom_patch_last_sample_duration(isom_file, trackNumber, next_dts);

    u64 EditTime, SegmentDuration, MediaTimeOut;
    GF_ISOEditType EditModeOut;
    gf_isom_get_edit(isom_file, trackNumber, edit_index, &EditTime, &SegmentDuration, &MediaTimeOut, &EditModeOut);

    GF_ISOTrackID reference_track_ID = *(GF_ISOTrackID *)(Data + sizeof(u32) * 2 + sizeof(u64) * 4);
    u64 decode_traf_time = *(u64 *)(Data + sizeof(u32) * 2 + sizeof(u64) * 5);
    u64 traf_duration = *(u64 *)(Data + sizeof(u32) * 2 + sizeof(u64) * 6);
    gf_isom_set_traf_mss_timeext(isom_file, reference_track_ID, decode_traf_time, traf_duration);

    u64 create_time = *(u64 *)(Data + sizeof(u32) * 2 + sizeof(u64) * 7);
    u64 modif_time = *(u64 *)(Data + sizeof(u32) * 2 + sizeof(u64) * 8);
    gf_isom_set_media_creation_time(isom_file, trackNumber, create_time, modif_time);

    if (Size >= sizeof(u32) * 4 + sizeof(u64) * 9) {
        u32 chunkNumber = *(u32 *)(Data + sizeof(u32) * 3 + sizeof(u64) * 9);
        u64 chunk_offset;
        u32 first_sample_num, sample_per_chunk, sample_desc_idx, cache_1 = 0, cache_2 = 0;
        gf_isom_get_chunk_info(isom_file, trackNumber, chunkNumber, &chunk_offset, &first_sample_num, &sample_per_chunk, &sample_desc_idx, &cache_1, &cache_2);
    }

    gf_isom_close(isom_file);
    return 0;
}