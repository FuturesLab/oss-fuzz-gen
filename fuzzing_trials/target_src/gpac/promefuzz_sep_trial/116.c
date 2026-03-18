// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_hint_max_chunk_duration at isom_write.c:5913:8 in isomedia.h
// gf_isom_add_track_to_root_od at isom_write.c:136:8 in isomedia.h
// gf_isom_remove_cenc_senc_box at drm_sample.c:996:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_rtp_set_timescale at hint_track.c:226:8 in isomedia.h
// gf_isom_remove_chapter at isom_write.c:3300:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_WRITE_EDIT, NULL);
    return iso_file;
}

int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Data[0];
    u32 maxChunkDur = Data[1];
    u32 trackID = Data[2];
    u32 hintDescriptionIndex = Data[3];
    u32 timeScale = Data[3];
    u32 chapterIndex = Data[3];

    // Fuzz gf_isom_hint_max_chunk_duration
    gf_isom_hint_max_chunk_duration(iso_file, trackNumber, maxChunkDur);

    // Fuzz gf_isom_add_track_to_root_od
    gf_isom_add_track_to_root_od(iso_file, trackNumber);

    // Fuzz gf_isom_remove_cenc_senc_box
    gf_isom_remove_cenc_senc_box(iso_file, trackNumber);

    // Fuzz gf_isom_set_track_id
    gf_isom_set_track_id(iso_file, trackNumber, trackID);

    // Fuzz gf_isom_rtp_set_timescale
    gf_isom_rtp_set_timescale(iso_file, trackNumber, hintDescriptionIndex, timeScale);

    // Fuzz gf_isom_remove_chapter
    gf_isom_remove_chapter(iso_file, trackNumber, chapterIndex);

    gf_isom_close(iso_file);
    return 0;
}