#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_has_meta_xml with gf_isom_get_meta_item_count

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_add_sample_aux_info
    u32 ret_gf_isom_probe_file_pqbcm = gf_isom_probe_file((const char *)data);
    u32 ret_gf_isom_text_sample_size_mhmby = gf_isom_text_sample_size(NULL);
    u32 ret_gf_isom_get_next_moof_number_vwcry = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_get_next_moof_number_rlgry = gf_isom_get_next_moof_number(file);
    u8 ret_gf_isom_get_mode_qqsod = gf_isom_get_mode(file);

    GF_Err ret_gf_isom_add_sample_aux_info_xbikh = gf_isom_add_sample_aux_info(file, ret_gf_isom_probe_file_pqbcm, ret_gf_isom_text_sample_size_mhmby, ret_gf_isom_get_next_moof_number_vwcry, ret_gf_isom_get_next_moof_number_rlgry, &ret_gf_isom_get_mode_qqsod, 0);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_get_meta_item_count(file, root_meta, track_num);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}