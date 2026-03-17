#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_is_adobe_protection_media
    u32 ret_gf_isom_get_next_alternate_group_id_vizrh = gf_isom_get_next_alternate_group_id(NULL);
    u32 ret_gf_isom_get_timescale_nnshq = gf_isom_get_timescale(file);

    Bool ret_gf_isom_is_adobe_protection_media_pmqht = gf_isom_is_adobe_protection_media(file, ret_gf_isom_get_next_alternate_group_id_vizrh, ret_gf_isom_get_timescale_nnshq);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_segment_get_fragment_count_mgrvt = gf_isom_segment_get_fragment_count(NULL);
    u32 ret_gf_isom_get_num_supported_boxes_dvuxl = gf_isom_get_num_supported_boxes();

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_num_supported_boxes to gf_isom_get_sample_sync
    u32 ret_gf_isom_get_copyright_count_lbusa = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_copyright_count_ttikx = gf_isom_get_copyright_count(NULL);

    Bool ret_gf_isom_get_sample_sync_avjkr = gf_isom_get_sample_sync(file, ret_gf_isom_get_copyright_count_ttikx, ret_gf_isom_get_num_supported_boxes_dvuxl);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_sample_sync to gf_isom_remove_track_reference
    u32 ret_gf_isom_get_pssh_count_orzdm = gf_isom_get_pssh_count(file);
    u32 ret_gf_isom_guess_specification_fkwgt = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_remove_track_reference_nsabk = gf_isom_remove_track_reference(file, ret_gf_isom_get_pssh_count_orzdm, ret_gf_isom_guess_specification_fkwgt);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_num_supported_boxes_fzhzf = gf_isom_get_num_supported_boxes();

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of gf_isom_probe_file
    u32 ret_gf_isom_probe_file_akhux = gf_isom_probe_file((const char *)data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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