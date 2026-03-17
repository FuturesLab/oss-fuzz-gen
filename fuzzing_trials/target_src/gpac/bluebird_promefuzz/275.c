#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Open the dummy file to simulate the ISO file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the file using the gpac API
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_275(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) {
        return 0;
    } // Ensure we have enough data

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 moof_index = *(u32 *)Data;
    u32 traf_index = *((u32 *)Data + 1);
    u32 trackNumber = *((u32 *)Data + 2);
    u64 decode_time = 0;

    // Fuzz gf_isom_segment_get_track_fragment_decode_time
    u32 track_id = gf_isom_segment_get_track_fragment_decode_time(isom_file, moof_index, traf_index, &decode_time);

    // Fuzz gf_isom_get_sample_description_index
    u64 for_time = (Size > sizeof(u32) * 3) ? *((u64 *)(Data + sizeof(u32) * 3)) : 0;
    u32 sample_desc_index = gf_isom_get_sample_description_index(isom_file, trackNumber, for_time);

    // Fuzz gf_isom_get_track_duration

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_track_duration with gf_isom_get_missing_bytes
    u64 track_duration = gf_isom_get_missing_bytes(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_sample_dts
    u32 sampleNumber = (Size > sizeof(u32) * 4) ? *((u32 *)(Data + sizeof(u32) * 4)) : 1;
    u64 sample_dts = gf_isom_get_sample_dts(isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_get_sample_from_dts
    u64 dts = (Size > sizeof(u32) * 5) ? *((u64 *)(Data + sizeof(u32) * 5)) : 0;
    u32 sample_from_dts = gf_isom_get_sample_from_dts(isom_file, trackNumber, dts);

    // Fuzz gf_isom_get_media_data_size
    u64 media_data_size = gf_isom_get_media_data_size(isom_file, trackNumber);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_media_data_size to gf_isom_get_last_producer_time_box
    u32 ret_gf_isom_get_next_moof_number_tiwgg = gf_isom_get_next_moof_number(isom_file);
    u64 ret_gf_isom_estimate_size_hwcme = gf_isom_estimate_size(isom_file);
    u64 ret_gf_isom_get_original_duration_emoiu = gf_isom_get_original_duration(isom_file);
    Bool ret_gf_isom_has_movie_xaspu = gf_isom_has_movie(isom_file);

    Bool ret_gf_isom_get_last_producer_time_box_xpyve = gf_isom_get_last_producer_time_box(isom_file, ret_gf_isom_get_next_moof_number_tiwgg, &ret_gf_isom_estimate_size_hwcme, &ret_gf_isom_get_original_duration_emoiu, ret_gf_isom_has_movie_xaspu);

    // End mutation: Producer.APPEND_MUTATOR

    cleanup_iso_file(isom_file);

    return 0;
}