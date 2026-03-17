#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const char *filename) {
    // Open the file in read/write mode, assuming a function for this exists.

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of gf_isom_open
    GF_ISOFile *isom_file = gf_isom_open(filename, GF_ISOM_OPEN_EDIT, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_222(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) {
        return 0;
    }

    // Create a dummy file to simulate the ISO file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *isom_file = initialize_iso_file("./dummy_file");
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 ref_type = *((u32 *)Data + 1);
    u32 group_id = *((u32 *)Data + 2);
    u32 max_chunk_size = *((u32 *)Data + 3);
    u32 new_media_type = *((u32 *)Data + 4);

    // Fuzz gf_isom_remove_track_from_root_od
    gf_isom_remove_track_from_root_od(isom_file, trackNumber);

    // Fuzz gf_isom_remove_track_reference
    gf_isom_remove_track_reference(isom_file, trackNumber, ref_type);

    // Fuzz gf_isom_set_track_interleaving_group

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_set_track_interleaving_group with gf_isom_set_brand_info

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_remove_track_reference to gf_isom_is_ismacryp_media
    u32 ret_gf_isom_get_next_alternate_group_id_brmqd = gf_isom_get_next_alternate_group_id(isom_file);
    u32 ret_gf_isom_get_track_count_bokei = gf_isom_get_track_count(isom_file);

    Bool ret_gf_isom_is_ismacryp_media_sliss = gf_isom_is_ismacryp_media(isom_file, ret_gf_isom_get_next_alternate_group_id_brmqd, ret_gf_isom_get_track_count_bokei);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_set_brand_info(isom_file, trackNumber, group_id);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_set_alternate_group_id

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_brand_info to gf_isom_remove_edit
    u32 ret_gf_isom_get_next_alternate_group_id_qfxac = gf_isom_get_next_alternate_group_id(NULL);
    u32 ret_gf_isom_get_supported_box_type_pmpzz = gf_isom_get_supported_box_type(0);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_remove_edit with gf_isom_remove_stream_description

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_remove_stream_description with gf_isom_check_data_reference
    GF_Err ret_gf_isom_remove_edit_cmlei = gf_isom_check_data_reference(isom_file, ret_gf_isom_get_next_alternate_group_id_qfxac, ret_gf_isom_get_supported_box_type_pmpzz);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_set_alternate_group_id(isom_file, trackNumber, group_id);

    // Fuzz gf_isom_hint_max_chunk_size
    gf_isom_hint_max_chunk_size(isom_file, trackNumber, max_chunk_size);

    // Fuzz gf_isom_set_media_type
    gf_isom_set_media_type(isom_file, trackNumber, new_media_type);

    cleanup_iso_file(isom_file);
    return 0;
}