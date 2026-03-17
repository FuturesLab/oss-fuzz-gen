#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = GF_FALSE;
    u32 track_num = 1; // Initialize with a non-zero value

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the ISO file using the temporary file path
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Fuzz the function-under-test
    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_set_media_type
    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_next_moof_number(file);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_moof_number to gf_isom_is_track_referenced
    gf_isom_enable_traf_map_templates(file);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_timescale with gf_isom_get_track_count
    u32 ret_gf_isom_get_timescale_rohfd = gf_isom_get_track_count(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR




    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_timescale to gf_isom_end_hint_sample
    u32 ret_gf_isom_probe_file_kpdtl = gf_isom_probe_file((const char *)"r");

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_probe_file to gf_isom_get_webvtt_config
    GF_Err ret_gf_isom_last_error_sccop = gf_isom_last_error(file);
    u32 ret_gf_isom_get_supported_box_type_bvutb = gf_isom_get_supported_box_type(ret_gf_isom_get_timescale_rohfd);

    const char * ret_gf_isom_get_webvtt_config_bqpec = gf_isom_get_webvtt_config(file, ret_gf_isom_get_supported_box_type_bvutb, ret_gf_isom_probe_file_kpdtl);
    if (ret_gf_isom_get_webvtt_config_bqpec == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    u8 ret_gf_isom_get_mode_yaztv = gf_isom_get_mode(NULL);

    GF_Err ret_gf_isom_end_hint_sample_wiaaa = gf_isom_end_hint_sample(file, ret_gf_isom_probe_file_kpdtl, ret_gf_isom_get_mode_yaztv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_is_track_referenced with gf_isom_get_nalu_length_field
    u32 ret_gf_isom_is_track_referenced_jtusw = gf_isom_get_nalu_length_field(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_get_timescale_rohfd);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}