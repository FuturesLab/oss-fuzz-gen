#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_release_segment
    Bool ret_gf_isom_moov_first_mysua = gf_isom_moov_first(file);

    GF_Err ret_gf_isom_release_segment_dxktn = gf_isom_release_segment(file, ret_gf_isom_moov_first_mysua);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_set_media_type with gf_isom_remove_edit

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_meta_item_has_ref
    GF_Err ret_gf_isom_remove_root_od_bcpfc = gf_isom_remove_root_od(file);
    Bool ret_gf_isom_moov_first_nchol = gf_isom_moov_first(file);
    u32 ret_gf_isom_segment_get_fragment_count_ocvth = gf_isom_segment_get_fragment_count(file);
    u32 ret_gf_isom_get_timescale_wxxou = gf_isom_get_timescale(file);

    u32 ret_gf_isom_meta_item_has_ref_orfwc = gf_isom_meta_item_has_ref(file, ret_gf_isom_moov_first_nchol, ret_gf_isom_segment_get_fragment_count_ocvth, ret_gf_isom_get_timescale_wxxou, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_remove_edit(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_media_type to gf_isom_enum_udta_keys
    u32 ret_gf_isom_probe_file_qgvjx = gf_isom_probe_file((const char *)"w");

    GF_Err ret_gf_isom_enum_udta_keys_wyzgs = gf_isom_enum_udta_keys(file, ret_gf_isom_probe_file_qgvjx, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}