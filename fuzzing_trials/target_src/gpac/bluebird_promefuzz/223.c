#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* open_dummy_isofile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void close_isofile(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
        remove("./dummy_file");
    }
}

int LLVMFuzzerTestOneInput_223(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    } // Ensure we have enough data for a track number

    GF_ISOFile *isom_file = open_dummy_isofile(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *((u32 *)Data);

    // Fuzz each target function with the dummy ISO file and trackNumber
    u32 max_sample_size = gf_isom_get_max_sample_size(isom_file, trackNumber);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_max_sample_size to gf_isom_setup_hint_track
    u32 ret_gf_isom_get_track_count_lvgrh = gf_isom_get_track_count(isom_file);

    GF_Err ret_gf_isom_setup_hint_track_rwdyo = gf_isom_setup_hint_track(isom_file, ret_gf_isom_get_track_count_lvgrh, 0);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_max_sample_delta with gf_isom_find_od_id_for_track
    u32 max_sample_delta = gf_isom_find_od_id_for_track(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_sync_point_count with gf_isom_get_media_timescale
    u32 sync_point_count = gf_isom_get_media_timescale(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    u32 avg_sample_size = gf_isom_get_avg_sample_size(isom_file, trackNumber);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_avg_sample_size to gf_isom_get_chunk_info
    Bool ret_gf_isom_is_smooth_streaming_moov_apnar = gf_isom_is_smooth_streaming_moov(isom_file);
    u64 ret_gf_isom_get_fragmented_duration_dpkhd = gf_isom_get_fragmented_duration(isom_file);
    u32 ret_gf_isom_get_supported_box_type_dzeef = gf_isom_get_supported_box_type(max_sample_delta);
    u32 ret_gf_isom_get_track_count_rhltr = gf_isom_get_track_count(NULL);
    u32 ret_gf_isom_guess_specification_nisxv = gf_isom_guess_specification(isom_file);

    GF_Err ret_gf_isom_get_chunk_info_jqqde = gf_isom_get_chunk_info(isom_file, sync_point_count, ret_gf_isom_get_track_count_lvgrh, &ret_gf_isom_get_fragmented_duration_dpkhd, &ret_gf_isom_get_track_count_lvgrh, &ret_gf_isom_get_supported_box_type_dzeef, &avg_sample_size, &ret_gf_isom_get_track_count_rhltr, &ret_gf_isom_guess_specification_nisxv);

    // End mutation: Producer.APPEND_MUTATOR

    u32 edits_count = gf_isom_get_edits_count(isom_file, trackNumber);

    // For gf_isom_get_mastering_display_colour_info, we need a sample description index
    if (Size >= 8) {
        u32 sampleDescriptionIndex = *((u32 *)(Data + 4));
        const GF_MasteringDisplayColourVolumeInfo *colour_info =
            gf_isom_get_mastering_display_colour_info(isom_file, trackNumber, sampleDescriptionIndex);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_use_compact_size
    u32 ret_gf_isom_get_supported_box_type_mtfoe = gf_isom_get_supported_box_type(0);
    Bool ret_gf_isom_has_movie_blhou = gf_isom_has_movie(NULL);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_use_compact_size with gf_isom_modify_alternate_brand
    GF_Err ret_gf_isom_use_compact_size_fxczl = gf_isom_modify_alternate_brand(isom_file, ret_gf_isom_get_supported_box_type_mtfoe, ret_gf_isom_has_movie_blhou);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_set_handler_name
    u32 ret_gf_isom_get_track_count_wyoax = gf_isom_get_track_count(isom_file);

    GF_Err ret_gf_isom_set_handler_name_bdjeh = gf_isom_set_handler_name(isom_file, ret_gf_isom_get_track_count_wyoax, (const char *)"r");

    // End mutation: Producer.APPEND_MUTATOR

    close_isofile(isom_file);
    return 0;
}