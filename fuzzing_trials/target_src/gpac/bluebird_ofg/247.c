#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_247(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_moof_number to gf_isom_get_tmcd_config
    u32 ret_gf_isom_get_timescale_xgcol = gf_isom_get_timescale(file);
    u32 ret_gf_isom_segment_get_fragment_count_yarad = gf_isom_segment_get_fragment_count(file);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_segment_get_fragment_count to gf_isom_set_fragment_reference_time
    u32 ret_gf_isom_get_copyright_count_tsqul = gf_isom_get_copyright_count(file);
    u64 ret_gf_isom_get_unused_box_bytes_ljdnm = gf_isom_get_unused_box_bytes(file);
    u64 ret_gf_isom_get_fragmented_duration_sptto = gf_isom_get_fragmented_duration(file);
    Bool ret_gf_isom_is_single_av_daffd = gf_isom_is_single_av(file);

    GF_Err ret_gf_isom_set_fragment_reference_time_fuqek = gf_isom_set_fragment_reference_time(file, ret_gf_isom_get_copyright_count_tsqul, ret_gf_isom_get_unused_box_bytes_ljdnm, ret_gf_isom_get_fragmented_duration_sptto, ret_gf_isom_is_single_av_daffd);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_next_alternate_group_id_rpmpa = gf_isom_get_next_alternate_group_id(file);

    GF_Err ret_gf_isom_get_tmcd_config_revnt = gf_isom_get_tmcd_config(NULL, ret_gf_isom_get_timescale_xgcol, ret_gf_isom_get_next_moof_number_hnobj, &ret_gf_isom_get_next_moof_number_hnobj, &ret_gf_isom_segment_get_fragment_count_yarad, &ret_gf_isom_get_next_alternate_group_id_rpmpa, NULL);

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