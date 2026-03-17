#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_rtp_set_time_sequence_offset with gf_isom_begin_hint_sample
    gf_isom_begin_hint_sample(isom_file, trackNumber, 0, 0);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    gf_isom_close(isom_file);
    return 0;
}