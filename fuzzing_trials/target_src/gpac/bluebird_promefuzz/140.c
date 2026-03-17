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

int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_max_sample_delta with gf_isom_get_media_type
    u32 max_sample_delta = gf_isom_get_media_type(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    u32 sync_point_count = gf_isom_get_sync_point_count(isom_file, trackNumber);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_avg_sample_size with gf_isom_get_track_kind_count
    u32 avg_sample_size = gf_isom_get_track_kind_count(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_track_kind_count to gf_isom_clone_sample_description
    u32 ret_gf_isom_get_track_count_vcjhx = gf_isom_get_track_count(isom_file);
    u32 ret_gf_isom_get_track_count_lnsdc = gf_isom_get_track_count(isom_file);
    u32 ret_gf_isom_get_timescale_wfgrn = gf_isom_get_timescale(isom_file);
    u32 ret_gf_isom_get_next_moof_number_lveju = gf_isom_get_next_moof_number(isom_file);
    u32 ret_gf_isom_get_track_count_qomfr = gf_isom_get_track_count(NULL);
    const char uzlvjizc[1024] = "byrpf";

    GF_Err ret_gf_isom_clone_sample_description_dizvo = gf_isom_clone_sample_description(isom_file, ret_gf_isom_get_track_count_lnsdc, isom_file, avg_sample_size, ret_gf_isom_get_next_moof_number_lveju, NULL, uzlvjizc, &ret_gf_isom_get_track_count_qomfr);

    // End mutation: Producer.APPEND_MUTATOR

    u32 edits_count = gf_isom_get_edits_count(isom_file, trackNumber);

    // For gf_isom_get_mastering_display_colour_info, we need a sample description index
    if (Size >= 8) {
        u32 sampleDescriptionIndex = *((u32 *)(Data + 4));
        const GF_MasteringDisplayColourVolumeInfo *colour_info =
            gf_isom_get_mastering_display_colour_info(isom_file, trackNumber, sampleDescriptionIndex);
    }

    close_isofile(isom_file);
    return 0;
}