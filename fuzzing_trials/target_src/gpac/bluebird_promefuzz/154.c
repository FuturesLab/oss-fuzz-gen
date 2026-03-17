#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    GF_ISOFile *iso_file = create_dummy_iso_file(Data, Size);
    if (!iso_file) {
        return 0;
    }

    u32 trackNumber = Data[0];
    s64 mediaOffset = 0;
    u32 moof_index = Data[1];
    GF_ISOTrackID trackID = Data[2];
    u32 MediaType = Data[3];
    u32 TimeScale = 1000;

    // Fuzz gf_isom_get_edit_list_type
    Bool isComplex = gf_isom_get_edit_list_type(iso_file, trackNumber, &mediaOffset);

    // Fuzz gf_isom_get_track_count
    u32 trackCount = gf_isom_get_track_count(iso_file);

    // Fuzz gf_isom_segment_get_track_fragment_count

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_segment_get_track_fragment_count with gf_isom_get_sync_point_count

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_sync_point_count with gf_isom_get_media_type
    u32 fragmentCount = gf_isom_get_media_type(iso_file, moof_index);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_media_type

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_media_type with gf_isom_get_track_kind_count
    u32 mediaType = gf_isom_get_track_kind_count(iso_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_cts_to_dts_shift

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_track_kind_count to gf_isom_has_sync_points
    u32 ret_gf_isom_get_next_alternate_group_id_tlvcl = gf_isom_get_next_alternate_group_id(iso_file);

    u8 ret_gf_isom_has_sync_points_oxvus = gf_isom_has_sync_points(iso_file, ret_gf_isom_get_next_alternate_group_id_tlvcl);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_sync_points to gf_isom_new_mj2k_description
    u32 ret_gf_isom_get_timescale_omavm = gf_isom_get_timescale(iso_file);
    u32 ret_gf_isom_get_next_moof_number_zzsvm = gf_isom_get_next_moof_number(iso_file);
    u32 ret_gf_isom_get_next_moof_number_ljzcp = gf_isom_get_next_moof_number(iso_file);
    u32 ret_gf_isom_get_next_alternate_group_id_pcjwc = gf_isom_get_next_alternate_group_id(iso_file);

    GF_Err ret_gf_isom_new_mj2k_description_tlchj = gf_isom_new_mj2k_description(iso_file, ret_gf_isom_get_next_moof_number_zzsvm, (const char *)"r", (const char *)Data, &ret_gf_isom_get_next_moof_number_ljzcp, &ret_gf_isom_has_sync_points_oxvus, ret_gf_isom_get_next_alternate_group_id_pcjwc);

    // End mutation: Producer.APPEND_MUTATOR

    s64 ctsToDtsShift = gf_isom_get_cts_to_dts_shift(iso_file, trackNumber);

    // Fuzz gf_isom_new_track
    u32 newTrackNumber = gf_isom_new_track(iso_file, trackID, MediaType, TimeScale);

    gf_isom_close(iso_file);
    return 0;
}