#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
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
    u32 ret_gf_isom_get_pssh_count_poavx = gf_isom_get_pssh_count(file);
    u32 ret_gf_isom_get_copyright_count_iayzv = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_copyright_count_ywetf = gf_isom_get_copyright_count(file);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_copyright_count to gf_isom_hint_direct_data
    u64 ret_gf_isom_get_unused_box_bytes_yknit = gf_isom_get_unused_box_bytes(file);
    u32 ret_gf_isom_get_supported_box_type_srvpv = gf_isom_get_supported_box_type(ret_gf_isom_get_next_moof_number_hnobj);
    u8 ret_gf_isom_get_mode_ldcma = gf_isom_get_mode(file);
    u8 yhuqqyll;
    memset(&yhuqqyll, 0, sizeof(yhuqqyll));

    GF_Err ret_gf_isom_hint_direct_data_fskzu = gf_isom_hint_direct_data(file, ret_gf_isom_get_copyright_count_iayzv, &yhuqqyll, ret_gf_isom_get_supported_box_type_srvpv, ret_gf_isom_get_mode_ldcma);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_segment_get_fragment_count_ripbi = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_set_sample_group_description_cffbq = gf_isom_set_sample_group_description(file, ret_gf_isom_get_copyright_count_qavcv, ret_gf_isom_get_pssh_count_poavx, ret_gf_isom_get_copyright_count_iayzv, 0, (void *)file, ret_gf_isom_get_copyright_count_ywetf, ret_gf_isom_segment_get_fragment_count_ripbi);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_sample_group_description to gf_isom_set_ismacryp_protection
    u32 ret_gf_isom_get_next_alternate_group_id_foviu = gf_isom_get_next_alternate_group_id(file);
    u32 ret_gf_isom_get_timescale_euaji = gf_isom_get_timescale(file);
    u32 ret_gf_isom_get_pssh_count_ymvoq = gf_isom_get_pssh_count(file);
    Bool ret_gf_isom_is_JPEG2000_bgypd = gf_isom_is_JPEG2000(NULL);
    u32 ret_gf_isom_get_copyright_count_hrsag = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_segment_get_fragment_count_rsgbx = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_set_ismacryp_protection_ypzrf = gf_isom_set_ismacryp_protection(file, ret_gf_isom_get_next_alternate_group_id_foviu, ret_gf_isom_get_copyright_count_ywetf, ret_gf_isom_get_timescale_euaji, ret_gf_isom_get_pssh_count_ymvoq, (char *)data, file, ret_gf_isom_is_JPEG2000_bgypd, ret_gf_isom_get_copyright_count_hrsag, ret_gf_isom_segment_get_fragment_count_rsgbx);

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl);

    return 0;
}