#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_next_alternate_group_id with gf_isom_get_timescale

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_fragment_append_data
    u32 ret_gf_isom_get_next_moof_number_dcpfz = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_get_pssh_count_obfly = gf_isom_get_pssh_count(file);
    u8 nunnteks;
    memset(&nunnteks, 0, sizeof(nunnteks));

    GF_Err ret_gf_isom_fragment_append_data_vkxyn = gf_isom_fragment_append_data(file, ret_gf_isom_get_next_moof_number_dcpfz, &nunnteks, ret_gf_isom_get_pssh_count_obfly, 0);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_next_alternate_group_id_zjvxa = gf_isom_get_timescale(NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    GF_Err ret_gf_isom_set_media_type_hrbtv = gf_isom_set_media_type(file, ret_gf_isom_get_next_alternate_group_id_zjvxa, 0);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}