#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_ac4_config_update
    u32 ret_gf_isom_get_num_supported_boxes_xqerq = gf_isom_get_num_supported_boxes();

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_num_supported_boxes to gf_isom_hevc_set_inband_config
    u32 ret_gf_isom_guess_specification_aunvr = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_hevc_set_inband_config_wpkps = gf_isom_hevc_set_inband_config(NULL, ret_gf_isom_guess_specification_aunvr, ret_gf_isom_get_num_supported_boxes_xqerq, 0);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_pssh_count_glrks = gf_isom_get_pssh_count(file);
    GF_AC4Config tbpmngmx;
    memset(&tbpmngmx, 0, sizeof(tbpmngmx));

    GF_Err ret_gf_isom_ac4_config_update_nwkug = gf_isom_ac4_config_update(file, ret_gf_isom_get_num_supported_boxes_xqerq, ret_gf_isom_get_pssh_count_glrks, &tbpmngmx);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}