// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_sample_flags at isom_write.c:8052:8 in isomedia.h
// gf_isom_set_ctts_v1 at isom_write.c:7867:8 in isomedia.h
// gf_isom_rtp_set_time_offset at hint_track.c:259:8 in isomedia.h
// gf_isom_purge_samples at isom_read.c:3192:8 in isomedia.h
// gf_isom_remove_sample at isom_write.c:1541:8 in isomedia.h
// gf_isom_hint_max_chunk_duration at isom_write.c:5913:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void close_dummy_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 6) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + 4));
    u32 isLeading = *((u32 *)(Data + 8));
    u32 dependsOn = *((u32 *)(Data + 12));
    u32 dependedOn = *((u32 *)(Data + 16));
    u32 redundant = *((u32 *)(Data + 20));
    
    gf_isom_set_sample_flags(iso_file, trackNumber, sampleNumber, isLeading, dependsOn, dependedOn, redundant);

    if (Size >= sizeof(u32) * 7) {
        u32 ctts_shift = *((u32 *)(Data + 24));
        gf_isom_set_ctts_v1(iso_file, trackNumber, ctts_shift);
    }

    if (Size >= sizeof(u32) * 9) {
        u32 HintDescriptionIndex = *((u32 *)(Data + 28));
        u32 TimeOffset = *((u32 *)(Data + 32));
        gf_isom_rtp_set_time_offset(iso_file, trackNumber, HintDescriptionIndex, TimeOffset);
    }

    if (Size >= sizeof(u32) * 10) {
        u32 nb_samples = *((u32 *)(Data + 36));
        gf_isom_purge_samples(iso_file, trackNumber, nb_samples);
    }

    if (Size >= sizeof(u32) * 11) {
        gf_isom_remove_sample(iso_file, trackNumber, sampleNumber);
    }

    if (Size >= sizeof(u32) * 12) {
        u32 maxChunkDur = *((u32 *)(Data + 40));
        gf_isom_hint_max_chunk_duration(iso_file, trackNumber, maxChunkDur);
    }

    close_dummy_iso_file(iso_file);
    return 0;
}