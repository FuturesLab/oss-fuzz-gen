#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of gf_isom_open
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, (const char *)data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Fuzz the function-under-test
    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_switch_parameters
    gf_isom_reset_switch_parameters(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_reset_switch_parameters to gf_isom_is_self_contained
    u32 ret_gf_isom_get_next_moof_number_dmxks = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_segment_get_fragment_count_hwrdd = gf_isom_segment_get_fragment_count(file);

    Bool ret_gf_isom_is_self_contained_nxtry = gf_isom_is_self_contained(file, ret_gf_isom_get_next_moof_number_dmxks, ret_gf_isom_segment_get_fragment_count_hwrdd);

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl);

    return 0;
}