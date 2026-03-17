#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_next_moof_number with gf_isom_get_track_count
    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_track_count(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_moof_number to gf_isom_is_track_referenced
    gf_isom_enable_traf_map_templates(file);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_timescale with gf_isom_get_next_moof_number
    u32 ret_gf_isom_get_timescale_rohfd = gf_isom_get_next_moof_number(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR




    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_timescale to gf_isom_rewrite_track_dependencies
    u32 ret_gf_isom_get_next_alternate_group_id_dbfvx = gf_isom_get_next_alternate_group_id(file);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_rewrite_track_dependencies with gf_isom_purge_track_reference
    GF_Err ret_gf_isom_rewrite_track_dependencies_xkthi = gf_isom_purge_track_reference(file, ret_gf_isom_get_next_alternate_group_id_dbfvx);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_is_track_referenced_jtusw = gf_isom_is_track_referenced(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_get_timescale_rohfd);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_rtp_set_time_sequence_offset
    u32 ret_gf_isom_get_next_alternate_group_id_klmut = gf_isom_get_next_alternate_group_id(file);
    u32 ret_gf_isom_get_copyright_count_jzkdt = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_supported_box_type_wuytd = gf_isom_get_supported_box_type(ret_gf_isom_get_timescale_rohfd);

    GF_Err ret_gf_isom_rtp_set_time_sequence_offset_lscay = gf_isom_rtp_set_time_sequence_offset(file, ret_gf_isom_get_next_alternate_group_id_klmut, ret_gf_isom_get_copyright_count_jzkdt, ret_gf_isom_get_supported_box_type_wuytd);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}