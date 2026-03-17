#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_estimate_size


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_set_image_sequence_coding_constraints
    u64 ret_gf_isom_get_first_mdat_start_fwmja = gf_isom_get_first_mdat_start(file);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_first_mdat_start to gf_isom_set_nalu_length_field

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_next_moof_number with gf_isom_guess_specification
    u32 ret_gf_isom_get_next_moof_number_rgsdw = gf_isom_guess_specification(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    u32 ret_gf_isom_segment_get_fragment_count_mejgo = gf_isom_segment_get_fragment_count(file);
    u32 ret_gf_isom_segment_get_fragment_count_sbjie = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_set_nalu_length_field_qejod = gf_isom_set_nalu_length_field(file, ret_gf_isom_get_next_moof_number_rgsdw, ret_gf_isom_segment_get_fragment_count_mejgo, ret_gf_isom_segment_get_fragment_count_sbjie);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_pssh_count_bnmdu = gf_isom_get_pssh_count(file);
    Bool ret_gf_isom_is_fragmented_cnmho = gf_isom_is_fragmented(file);
    Bool ret_gf_isom_has_movie_jaqhe = gf_isom_has_movie(NULL);
    Bool ret_gf_isom_is_smooth_streaming_moov_uqlkz = gf_isom_is_smooth_streaming_moov(file);
    u32 ret_gf_isom_get_copyright_count_mcauv = gf_isom_get_copyright_count(file);

    GF_Err ret_gf_isom_set_image_sequence_coding_constraints_ekhzf = gf_isom_set_image_sequence_coding_constraints(file, ret_gf_isom_get_pssh_count_bnmdu, ret_gf_isom_guess_specification_cnshv, ret_gf_isom_is_fragmented_cnmho, ret_gf_isom_has_movie_jaqhe, ret_gf_isom_is_smooth_streaming_moov_uqlkz, ret_gf_isom_get_copyright_count_mcauv);

    // End mutation: Producer.APPEND_MUTATOR

    u64 ret_gf_isom_estimate_size_zmomf = gf_isom_estimate_size(file);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}