// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_sample_padding at isom_read.c:2492:8 in isomedia.h
// gf_isom_fragment_set_sample_roll_group at isom_write.c:7780:8 in isomedia.h
// gf_isom_purge_samples at isom_read.c:3192:8 in isomedia.h
// gf_isom_set_sample_roll_group at isom_write.c:7770:8 in isomedia.h
// gf_isom_set_alternate_group_id at isom_write.c:6862:8 in isomedia.h
// gf_isom_rtp_set_time_sequence_offset at hint_track.c:292:8 in isomedia.h
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

int LLVMFuzzerTestOneInput_210(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 padding_bytes = *(u32 *)(Data + sizeof(u32));
    u32 sampleNumber = *(u32 *)(Data + 2 * sizeof(u32));
    u32 groupId = *(u32 *)(Data + 3 * sizeof(u32));

    // Fuzz gf_isom_set_sample_padding
    gf_isom_set_sample_padding(isom_file, trackNumber, padding_bytes);

    // Fuzz gf_isom_fragment_set_sample_roll_group
    gf_isom_fragment_set_sample_roll_group(isom_file, trackNumber, sampleNumber, GF_ISOM_SAMPLE_PREROLL_NONE, 0);

    // Fuzz gf_isom_purge_samples
    gf_isom_purge_samples(isom_file, trackNumber, 1);

    // Fuzz gf_isom_set_sample_roll_group
    gf_isom_set_sample_roll_group(isom_file, trackNumber, sampleNumber, GF_ISOM_SAMPLE_PREROLL_NONE, 0);

    // Fuzz gf_isom_set_alternate_group_id
    gf_isom_set_alternate_group_id(isom_file, trackNumber, groupId);

    // Fuzz gf_isom_rtp_set_time_sequence_offset
    gf_isom_rtp_set_time_sequence_offset(isom_file, trackNumber, 0, 0);

    gf_isom_close(isom_file);
    return 0;
}