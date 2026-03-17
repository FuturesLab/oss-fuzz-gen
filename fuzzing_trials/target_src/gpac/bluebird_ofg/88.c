#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_next_moof_number to gf_isom_get_sample_rap_roll_info
    u32 ret_gf_isom_get_next_alternate_group_id_rzjvs = gf_isom_get_next_alternate_group_id(NULL);
    u32 ret_gf_isom_get_pssh_count_bqthy = gf_isom_get_pssh_count(file);
    Bool ret_gf_isom_has_movie_haeey = gf_isom_has_movie(file);
    s32 mhetvcbr;
    memset(&mhetvcbr, 0, sizeof(mhetvcbr));

    GF_Err ret_gf_isom_get_sample_rap_roll_info_nimly = gf_isom_get_sample_rap_roll_info(file, ret_gf_isom_get_next_alternate_group_id_rzjvs, ret_gf_isom_get_pssh_count_bqthy, &ret_gf_isom_has_movie_haeey, NULL, &mhetvcbr);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_text_add_karaoke

    GF_Err ret_gf_isom_text_add_karaoke_vwpyb = gf_isom_text_add_karaoke(NULL, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_media_type to gf_isom_set_track_enabled
    u32 ret_gf_isom_get_timescale_mwctn = gf_isom_get_timescale(file);
    Bool ret_gf_isom_moov_first_drkes = gf_isom_moov_first(file);

    GF_Err ret_gf_isom_set_track_enabled_wabct = gf_isom_set_track_enabled(file, ret_gf_isom_get_timescale_mwctn, ret_gf_isom_moov_first_drkes);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}