#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_truehd_config_get
    u32 ret_gf_isom_get_track_count_inrmv = gf_isom_get_track_count(file);
    u32 ret_gf_isom_get_track_count_akfrt = gf_isom_get_track_count(file);
    u32 ret_gf_isom_get_timescale_xqpkj = gf_isom_get_timescale(file);
    u32 ret_gf_isom_get_supported_box_type_juwxt = gf_isom_get_supported_box_type(0);

    GF_Err ret_gf_isom_truehd_config_get_sjijq = gf_isom_truehd_config_get(file, ret_gf_isom_get_track_count_inrmv, ret_gf_isom_get_track_count_akfrt, &ret_gf_isom_get_timescale_xqpkj, &ret_gf_isom_get_supported_box_type_juwxt);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_set_media_type with gf_isom_remove_chapter
    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_remove_chapter(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}