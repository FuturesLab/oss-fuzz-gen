#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const char *filename) {
    // Open the file in read/write mode, assuming a function for this exists.
    GF_ISOFile *isom_file = gf_isom_open(filename, GF_ISOM_OPEN_EDIT, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
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
    gf_isom_set_track_interleaving_group(isom_file, trackNumber, group_id);

    // Fuzz gf_isom_set_alternate_group_id
    gf_isom_set_alternate_group_id(isom_file, trackNumber, group_id);

    // Fuzz gf_isom_hint_max_chunk_size

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_hint_max_chunk_size with gf_isom_set_last_sample_duration
    gf_isom_set_last_sample_duration(isom_file, trackNumber, max_chunk_size);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_set_media_type
    gf_isom_set_media_type(isom_file, trackNumber, new_media_type);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_webvtt_config
    u32 ret_gf_isom_get_next_alternate_group_id_gnnzg = gf_isom_get_next_alternate_group_id(NULL);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_alternate_group_id to gf_isom_track_cenc_add_sample_info
    u32 ret_gf_isom_get_copyright_count_hqqef = gf_isom_get_copyright_count(isom_file);
    u32 ret_gf_isom_get_track_count_wrntv = gf_isom_get_track_count(isom_file);
    u32 ret_gf_isom_probe_file_lbwfj = gf_isom_probe_file((const char *)"w");
    Bool ret_gf_isom_is_JPEG2000_giauh = gf_isom_is_JPEG2000(isom_file);
    Bool ret_gf_isom_is_JPEG2000_atvsp = gf_isom_is_JPEG2000(NULL);
    Bool ret_gf_isom_moov_first_guwey = gf_isom_moov_first(isom_file);
    u8 icunzqyr;
    memset(&icunzqyr, 0, sizeof(icunzqyr));

    GF_Err ret_gf_isom_track_cenc_add_sample_info_cgzfd = gf_isom_track_cenc_add_sample_info(isom_file, ret_gf_isom_get_track_count_wrntv, ret_gf_isom_probe_file_lbwfj, &icunzqyr, ret_gf_isom_get_next_alternate_group_id_gnnzg, ret_gf_isom_is_JPEG2000_giauh, ret_gf_isom_is_JPEG2000_atvsp, ret_gf_isom_moov_first_guwey);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_num_supported_boxes_tucri = gf_isom_get_num_supported_boxes();

    const char * ret_gf_isom_get_webvtt_config_jxeeo = gf_isom_get_webvtt_config(isom_file, ret_gf_isom_get_next_alternate_group_id_gnnzg, ret_gf_isom_get_num_supported_boxes_tucri);
    if (ret_gf_isom_get_webvtt_config_jxeeo == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cleanup_iso_file(isom_file);
    return 0;
}