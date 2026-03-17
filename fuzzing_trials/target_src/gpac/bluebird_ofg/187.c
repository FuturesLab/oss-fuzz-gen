#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
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
    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_reset_alt_brands to gf_isom_set_sample_group_description
    u32 ret_gf_isom_get_copyright_count_qrehu = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_segment_get_fragment_count_qmhxb = gf_isom_segment_get_fragment_count(file);
    u32 ret_gf_isom_get_pssh_count_jrkrt = gf_isom_get_pssh_count(file);
    GF_ISMASample * ret_gf_isom_ismacryp_new_sample_bsksh = gf_isom_ismacryp_new_sample();
    if (ret_gf_isom_ismacryp_new_sample_bsksh == NULL){
    	return 0;
    }
    u32 ret_gf_isom_segment_get_fragment_count_wyfda = gf_isom_segment_get_fragment_count(file);
    u32 ret_gf_isom_get_track_count_cnwuw = gf_isom_get_track_count(file);

    GF_Err ret_gf_isom_set_sample_group_description_wbunr = gf_isom_set_sample_group_description(file, ret_gf_isom_get_copyright_count_qrehu, ret_gf_isom_segment_get_fragment_count_qmhxb, ret_gf_isom_get_pssh_count_jrkrt, ret_gf_isom_get_next_moof_number_hnobj, (void *)ret_gf_isom_ismacryp_new_sample_bsksh, ret_gf_isom_segment_get_fragment_count_wyfda, ret_gf_isom_get_track_count_cnwuw);

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl);

    return 0;
}