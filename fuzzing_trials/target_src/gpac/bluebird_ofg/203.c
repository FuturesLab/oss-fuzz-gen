#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_sample_get_subsample
    u32 ret_gf_isom_segment_get_fragment_count_mgrvt = gf_isom_segment_get_fragment_count(NULL);
    u32 ret_gf_isom_get_num_supported_boxes_dvuxl = gf_isom_get_num_supported_boxes();

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_num_supported_boxes to gf_isom_get_sample_sync

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_num_supported_boxes to gf_isom_update_sample
    const u32 * ret_gf_isom_get_brands_eytph = gf_isom_get_brands(file);
    if (ret_gf_isom_get_brands_eytph == NULL){
    	return 0;
    }
    u32 ret_gf_isom_get_pssh_count_hnqqp = gf_isom_get_pssh_count(file);
    Bool ret_gf_isom_is_JPEG2000_towkk = gf_isom_is_JPEG2000(NULL);
    GF_ISOSample gsrcakip;
    memset(&gsrcakip, 0, sizeof(gsrcakip));

    GF_Err ret_gf_isom_update_sample_vayfu = gf_isom_update_sample(file, ret_gf_isom_get_num_supported_boxes_dvuxl, ret_gf_isom_get_pssh_count_hnqqp, &gsrcakip, ret_gf_isom_is_JPEG2000_towkk);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_copyright_count_lbusa = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_copyright_count_ttikx = gf_isom_get_copyright_count(NULL);

    Bool ret_gf_isom_get_sample_sync_avjkr = gf_isom_get_sample_sync(file, ret_gf_isom_get_copyright_count_ttikx, ret_gf_isom_get_num_supported_boxes_dvuxl);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_num_supported_boxes_fzhzf = gf_isom_get_num_supported_boxes();
    u32 ret_gf_isom_probe_file_akhux = gf_isom_probe_file((const char *)"r");
    u32 ret_gf_isom_get_supported_box_type_taydb = gf_isom_get_supported_box_type(0);
    Bool ret_gf_isom_is_single_av_lkoeq = gf_isom_is_single_av(file);
    u8 eolnozag;
    memset(&eolnozag, 0, sizeof(eolnozag));

    GF_Err ret_gf_isom_sample_get_subsample_grmgu = gf_isom_sample_get_subsample(file, ret_gf_isom_segment_get_fragment_count_mgrvt, ret_gf_isom_get_num_supported_boxes_dvuxl, ret_gf_isom_get_num_supported_boxes_fzhzf, ret_gf_isom_probe_file_akhux, &ret_gf_isom_get_supported_box_type_taydb, &eolnozag, NULL, &ret_gf_isom_is_single_av_lkoeq);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_set_media_type

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_next_moof_number with gf_isom_get_copyright_count
    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_copyright_count(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}