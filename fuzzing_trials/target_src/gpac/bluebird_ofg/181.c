#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_moof_number to gf_isom_mvc_config_new
    u32 ret_gf_isom_get_copyright_count_lyknq = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_num_supported_boxes_yajaf = gf_isom_get_num_supported_boxes();
    GF_AVCConfig gxkdwaak;
    memset(&gxkdwaak, 0, sizeof(gxkdwaak));
    const char dwwukztr[1024] = "yzmvk";

    GF_Err ret_gf_isom_mvc_config_new_kvqax = gf_isom_mvc_config_new(file, ret_gf_isom_get_num_supported_boxes_yajaf, &gxkdwaak, (const char *)data, dwwukztr, &ret_gf_isom_get_next_moof_number_hnobj);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_mvc_config_new to gf_isom_rewrite_track_dependencies


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_rewrite_track_dependencies with gf_isom_set_inplace_padding
    GF_Err ret_gf_isom_rewrite_track_dependencies_whwbw = gf_isom_set_inplace_padding(file, ret_gf_isom_get_next_moof_number_hnobj);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_fragment_set_sample_roll_group
    u32 ret_gf_isom_segment_get_fragment_count_srixm = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_fragment_set_sample_roll_group_zmubd = gf_isom_fragment_set_sample_roll_group(file, ret_gf_isom_guess_specification_cnshv, 0, 0, 0);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}