// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_track_matrix at isom_write.c:5254:8 in isomedia.h
// gf_isom_shift_cts_offset at isom_write.c:5187:8 in isomedia.h
// gf_isom_set_ctts_v1 at isom_write.c:7867:8 in isomedia.h
// gf_isom_new_hint_description at hint_track.c:170:8 in isomedia.h
// gf_isom_rtp_packet_set_offset at hint_track.c:653:8 in isomedia.h
// gf_isom_hint_max_chunk_duration at isom_write.c:5913:8 in isomedia.h
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

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5 + sizeof(s32) * 11 + sizeof(u8)) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 offset = 0;
    u32 trackNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    s32 matrix[9];
    for (int i = 0; i < 9; i++) {
        matrix[i] = *(s32 *)(Data + offset);
        offset += sizeof(s32);
    }

    s32 offset_shift = *(s32 *)(Data + offset);
    offset += sizeof(s32);

    u32 ctts_shift = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    s32 HintTrackVersion = *(s32 *)(Data + offset);
    offset += sizeof(s32);

    s32 LastCompatibleVersion = *(s32 *)(Data + offset);
    offset += sizeof(s32);

    u8 Rely = *(u8 *)(Data + offset);
    offset += sizeof(u8);

    u32 HintDescriptionIndex;

    write_dummy_file(Data, Size);

    gf_isom_set_track_matrix(isom_file, trackNumber, matrix);
    gf_isom_shift_cts_offset(isom_file, trackNumber, offset_shift);
    gf_isom_set_ctts_v1(isom_file, trackNumber, ctts_shift);
    gf_isom_new_hint_description(isom_file, trackNumber, HintTrackVersion, LastCompatibleVersion, Rely, &HintDescriptionIndex);
    gf_isom_rtp_packet_set_offset(isom_file, trackNumber, offset_shift);
    gf_isom_hint_max_chunk_duration(isom_file, trackNumber, ctts_shift);

    gf_isom_close(isom_file);

    return 0;
}