#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
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
    const char * ret_gf_isom_get_filename_hsbfq = gf_isom_get_filename(file);
    if (ret_gf_isom_get_filename_hsbfq == NULL){
    	return 0;
    }
    u32 ret_gf_isom_get_copyright_count_qavcv = gf_isom_get_copyright_count(file);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_pssh_count with gf_isom_get_timescale

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_timescale with gf_isom_guess_specification
    u32 ret_gf_isom_get_pssh_count_poavx = gf_isom_guess_specification(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_pssh_count to gf_isom_get_sample_to_group_info
    u32 ret_gf_isom_get_next_alternate_group_id_huruy = gf_isom_get_next_alternate_group_id(file);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_alternate_group_id to gf_isom_get_stsd_template
    gf_isom_reset_sample_count(file);
    u32 ret_gf_isom_get_track_count_cjfdg = gf_isom_get_track_count(file);
    u32 ret_gf_isom_get_next_moof_number_favls = gf_isom_get_next_moof_number(file);
    u8 *gpasmemc;
    memset(&gpasmemc, 0, sizeof(gpasmemc));

    GF_Err ret_gf_isom_get_stsd_template_htqdd = gf_isom_get_stsd_template(file, ret_gf_isom_get_track_count_cjfdg, ret_gf_isom_get_next_alternate_group_id_huruy, &gpasmemc, &ret_gf_isom_get_next_moof_number_favls);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_track_count_wfcab = gf_isom_get_track_count(file);
    u32 ret_gf_isom_get_next_alternate_group_id_kgehm = gf_isom_get_next_alternate_group_id(file);

    GF_Err ret_gf_isom_get_sample_to_group_info_xdqhh = gf_isom_get_sample_to_group_info(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_get_next_alternate_group_id_huruy, ret_gf_isom_get_track_count_wfcab, ret_gf_isom_get_next_alternate_group_id_kgehm, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_copyright_count_iayzv = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_copyright_count_ywetf = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_segment_get_fragment_count_ripbi = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_set_sample_group_description_cffbq = gf_isom_set_sample_group_description(file, ret_gf_isom_get_copyright_count_qavcv, ret_gf_isom_get_pssh_count_poavx, ret_gf_isom_get_copyright_count_iayzv, 0, (void *)file, ret_gf_isom_get_copyright_count_ywetf, ret_gf_isom_segment_get_fragment_count_ripbi);

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl);

    return 0;
}