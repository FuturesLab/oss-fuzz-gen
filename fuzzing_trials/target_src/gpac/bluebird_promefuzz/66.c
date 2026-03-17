#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* open_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Assuming we have a function to open an ISO file from a file path.
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void close_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    GF_ISOFile *isom_file = open_dummy_iso_file(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = Data[0] % 256; // Simple way to get a track number
    u32 sampleDescriptionIndex = Data[1] % 256; // Simple way to get a sample description index

    // Fuzz gf_isom_get_avg_sample_delta
    u32 avg_sample_delta = gf_isom_get_avg_sample_delta(isom_file, trackNumber);

    // Fuzz gf_isom_get_payt_count

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_payt_count with gf_isom_segment_get_track_fragment_count
    u32 payt_count = gf_isom_segment_get_track_fragment_count(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_track_count
    u32 track_count = gf_isom_get_track_count(isom_file);

    // Fuzz gf_isom_get_track_kind_count

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_track_kind_count with gf_isom_get_media_timescale
    u32 track_kind_count = gf_isom_get_media_timescale(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_sample_count

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_media_timescale to gf_isom_get_media_language

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_media_timescale to gf_isom_set_alternate_group_id
    GF_Err ret_gf_isom_update_duration_vujwb = gf_isom_update_duration(isom_file);
    u32 ret_gf_isom_get_track_count_eaqzg = gf_isom_get_track_count(isom_file);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_set_alternate_group_id with gf_isom_purge_samples
    GF_Err ret_gf_isom_set_alternate_group_id_uepcz = gf_isom_purge_samples(isom_file, ret_gf_isom_get_track_count_eaqzg, track_kind_count);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    u64 ret_gf_isom_get_fragmented_duration_slmbm = gf_isom_get_fragmented_duration(isom_file);

    GF_Err ret_gf_isom_get_media_language_exkzq = gf_isom_get_media_language(isom_file, track_kind_count, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    u32 sample_count = gf_isom_get_sample_count(isom_file, trackNumber);

    // Fuzz gf_isom_get_vvc_type
    GF_ISOMVVCType vvc_type = gf_isom_get_vvc_type(isom_file, trackNumber, sampleDescriptionIndex);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_fragment_defaults
    u32 ret_gf_isom_get_copyright_count_cpfhy = gf_isom_get_copyright_count(isom_file);
    u32 ret_gf_isom_get_copyright_count_ccbpl = gf_isom_get_copyright_count(isom_file);
    u32 ret_gf_isom_get_next_alternate_group_id_mhxfj = gf_isom_get_next_alternate_group_id(NULL);
    u32 ret_gf_isom_get_next_moof_number_jakrl = gf_isom_get_next_moof_number(isom_file);
    u32 ret_gf_isom_guess_specification_bgaqb = gf_isom_guess_specification(isom_file);
    u8 jlsoioaq;
    memset(&jlsoioaq, 0, sizeof(jlsoioaq));
    u16 fbglqqap;
    memset(&fbglqqap, 0, sizeof(fbglqqap));

    GF_Err ret_gf_isom_get_fragment_defaults_nwbzf = gf_isom_get_fragment_defaults(isom_file, ret_gf_isom_get_copyright_count_cpfhy, &ret_gf_isom_get_copyright_count_ccbpl, &ret_gf_isom_get_next_alternate_group_id_mhxfj, &ret_gf_isom_get_next_moof_number_jakrl, &ret_gf_isom_guess_specification_bgaqb, &jlsoioaq, &fbglqqap);

    // End mutation: Producer.APPEND_MUTATOR

    close_iso_file(isom_file);
    return 0;
}