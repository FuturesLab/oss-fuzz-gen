#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_fragment_set_sample_roll_group

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_pssh_count with gf_isom_segment_get_fragment_count
    u32 ret_gf_isom_get_pssh_count_ljdty = gf_isom_segment_get_fragment_count(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_segment_get_fragment_count to gf_isom_set_media_timescale
    GF_Err ret_gf_isom_remove_root_od_yfkkc = gf_isom_remove_root_od(file);
    u32 ret_gf_isom_guess_specification_ujfzr = gf_isom_guess_specification(file);
    u32 ret_gf_isom_get_track_count_nuqta = gf_isom_get_track_count(NULL);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_track_count to gf_isom_allocate_sidx
    u64 ret_gf_isom_get_duration_wfaoa = gf_isom_get_duration(file);
    Bool ret_gf_isom_needs_layer_reconstruction_xkpxu = gf_isom_needs_layer_reconstruction(NULL);
    u32 ret_gf_isom_get_timescale_jruvr = gf_isom_get_timescale(file);
    u32 ret_gf_isom_get_pssh_count_ypryq = gf_isom_get_pssh_count(file);
    u32 ret_gf_isom_get_next_alternate_group_id_vyjfe = gf_isom_get_next_alternate_group_id(file);
    Bool ret_gf_isom_is_fragmented_zvacu = gf_isom_is_fragmented(file);

    GF_Err ret_gf_isom_allocate_sidx_bobka = gf_isom_allocate_sidx(file, 0, ret_gf_isom_needs_layer_reconstruction_xkpxu, ret_gf_isom_get_timescale_jruvr, &ret_gf_isom_get_pssh_count_ypryq, &ret_gf_isom_get_next_alternate_group_id_vyjfe, &ret_gf_isom_get_track_count_nuqta, ret_gf_isom_is_fragmented_zvacu);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_timescale_rldky = gf_isom_set_media_timescale(file, ret_gf_isom_guess_specification_ujfzr, ret_gf_isom_get_track_count_nuqta, ret_gf_isom_get_pssh_count_ljdty, ret_gf_isom_get_pssh_count_ljdty);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_probe_file_sukka = gf_isom_probe_file((const char *)"w");

    GF_Err ret_gf_isom_fragment_set_sample_roll_group_hsdvc = gf_isom_fragment_set_sample_roll_group(file, ret_gf_isom_get_pssh_count_ljdty, ret_gf_isom_probe_file_sukka, 0, 0);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}